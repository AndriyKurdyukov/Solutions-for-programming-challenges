/*
Author: Andriy Kuryukov
Year: 2021
This code is a part of my hobby project and is free to use and redistribute in any form.
*/
#include <iostream>
#include <algorithm>
#include "sudoku.h"

Sudoku::Sudoku(int input[9][9]) {
  std::vector<inf> row_vec = {};  // iterate over the input
  inf cell_info = {};
  vec_info.reserve(81);
  for ( int row = 0; row < 9; row++ ) {
    row_vec.clear();
    for ( int col = 0; col < 9; col++ ) {
      if (input[row][col] == 0) {     // mark as empty cell that can be changed
        cell_info.is_chosen = false;
        cell_info.is_given = false;
        row_vec.push_back(cell_info);
        cell_info = {};
      } else {
        cell_info.is_chosen = false;
        cell_info.is_given = true;
        cell_info.start.push_back(input[row][col]);  // initialize given cells 
        cell_info.current.push_back(input[row][col]);
        row_vec.push_back(cell_info);
        cell_info = {};
      }
    }
    vec_info.push_back(row_vec);
  }
  // now initialize the starting = current number candidates for not given cells
  for ( int row = 0; row < 9; row++ ) {
    for ( int col = 0; col < 9; col++ ) {
      fill_candidates(row, col, vec_info);
    }
  }
}
void Sudoku::fill_candidates(int row, int col, std::vector<std::vector<inf>>& vec) {
  std::vector<int> start_candidates{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> row_res, col_res, box_res = {};
  std::vector<int> row_col_box_union = {};
  std::vector<int> final_candidates = {};
  if ( !(vec.at(row)).at(col).is_given ) {
    row_res = check_row(row, vec, 0, 0);
    col_res = check_row(col, vec, 1, 0);
    box_res = check_box(row, col, vec, 0);
    // calculate union of numbers from row, column and box, and subtract from set of nums 1-9
    row_col_box_union = set_op(set_op(row_res, col_res, 0), box_res, 0);
    final_candidates = set_op(start_candidates, row_col_box_union, 1);
    // put final canidates into starting stack
    vec.at(row).at(col).start = final_candidates;
    vec.at(row).at(col).current = final_candidates;
    } else {
      return;
  }
}
std::vector<int> Sudoku::check_row(int row, std::vector<std::vector<inf>> vec, bool param1, bool given_or_chosen) {
  std::vector<int> result = {};  // param=0 for rows, 1 for columns
  result.reserve(9);
  bool condition = false;
  switch (param1) {
    case 0:
      for ( int col = 0; col < 9; col++ ) {
        switch (given_or_chosen) {
          case 0:
            if ( (vec.at(row)).at(col).is_given ) {    // look at given cells only
              result.push_back(vec.at(row).at(col).start.front());
            }
            break;
          case 1:
            if ( (vec.at(row)).at(col).is_chosen ) {    // look at chosen cells only
              result.push_back(vec.at(row).at(col).current.back());
            }
            break;
        }
      }
      return result;
    case 1:
      for ( int col = 0; col < 9; col++ ) {
          switch (given_or_chosen) {
          case 0:
            if ( (vec.at(col)).at(row).is_given ) {    // look at given cells only
              result.push_back(vec.at(col).at(row).start.front());
            }
            break;
          case 1:
            if ( (vec.at(col)).at(row).is_chosen ) {    // look at chosen cells only
              result.push_back(vec.at(col).at(row).current.back());
            }
            break;
          }
      }
      return result;
  }
}
std::vector<int> Sudoku::check_box(int row, int col, std::vector<std::vector<inf>> vec, bool given_or_chosen) {
  int box_row = row/3;  // corrdinates of needed 3x3 box
  int box_col = col/3;
  std::vector<int> result = {};
  result.reserve(9);
  inf current_cell = {};
  bool condition = false;
  for ( int row = 0; row < 9; row++ ) {
    current_cell = vec.at(box_row * 3 + row % 3).at(box_col * 3 + row / 3);
    switch ( given_or_chosen ) {
      case 0:
        if ( current_cell.is_given ) {
          result.push_back(current_cell.start.front());
        }
        break;
      case 1:
        if ( current_cell.is_chosen ) {  // check  chosen cells, last numbers are the ones chosen
          result.push_back(current_cell.current.back());
        }
        break;
    }
  }
  return result;
}
// set operation on vectors: param=0 for union, 1 for difference
std::vector<int> Sudoku::set_op(std::vector<int> set1, std::vector<int> set2, bool param) {
  // sort both vectors
  std::vector<int>::iterator ip1, ip2;
  std::sort(set1.begin(), set1.end());
  std::sort(set2.begin(), set2.end());
  ip1 = std::unique(set1.begin(), set1.end());
  ip2 = std::unique(set2.begin(), set2.end());
  set1.resize(std::distance(set1.begin(), ip1));  // delete duplicates and sort
  set2.resize(std::distance(set2.begin(), ip2));
  std::vector<int> result;
  switch (param) {
    case 0:
      std::set_union(set1.begin(),
                     set1.end(), set2.begin(), set2.end(),
                     std::back_inserter(result));
      break;
    case 1:
      std::set_difference(set1.begin(),
                 set1.end(), set2.begin(), set2.end(),
                 std::back_inserter(result));
      break;
  }
  return result;
}
std::vector<std::vector<int>> Sudoku::solve_sudoku() {
  int n = 0;
  int row = 0;
  int col = 0;
  std::vector<int> curr_num = {};
  bool cond_sat = false;
  enum State{CHECK, CHECK_B4_DEL, CHOOSE_ELEM, DELETE_ELEM, RESTORE};
  State s = CHECK;
  while ( n < 81 ) {
    row = n / 9;
    col = n % 9;
    if ( n < 0 ) {
      throw std::runtime_error("No solution exits");
    }
    switch (s) {
      case CHECK:
        if ( !vec_info.at(row).at(col).is_given ) {
          s = CHOOSE_ELEM;
        } else {
          n++;
        }
        break;
      case CHECK_B4_DEL:
        if ( !vec_info.at(row).at(col).is_given ) {
          s = DELETE_ELEM;
        } else {
          n--;
        }
        break;
      case CHOOSE_ELEM:
        vec_info.at(row).at(col).is_chosen = false;
        curr_num.push_back(vec_info.at(row).at(col).current.back());  // take last number as current
        cond_sat = (set_op(curr_num, check_box(row, col, vec_info, 1), 1).size() == 1);
        cond_sat = cond_sat && (set_op(curr_num, check_row(row, vec_info, 0, 1), 1).size() == 1);
        cond_sat = cond_sat && (set_op(curr_num, check_row(col, vec_info, 1, 1), 1).size() == 1);
        curr_num.clear();
        if (cond_sat) {  // if chosen number satisfies
          vec_info.at(row).at(col).is_chosen = true;  // mark number as chosen
          s = CHECK;  // set state to check, check if number given or chosen
          n++;  // go to next element
        } else {
          s = DELETE_ELEM;  // else try to delete it
          vec_info.at(row).at(col).is_chosen = false;
        }
        break;
      case DELETE_ELEM:
        if (vec_info.at(row).at(col).current.size() <= 1) {   // if empty after deleting, go to restore and backtrack
          s = RESTORE;
        } else {
          vec_info.at(row).at(col).current.pop_back();
          s = CHOOSE_ELEM;  // if not empty delete last elem than choose a different element
        }
        vec_info.at(row).at(col).is_chosen = false;
        break;
      case RESTORE:
        vec_info.at(row).at(col).current.clear();
        vec_info.at(row).at(col).current = vec_info.at(row).at(col).start;   // restore starting values
        vec_info.at(row).at(col).is_chosen = false;
        n--;  // go back
        s = CHECK_B4_DEL;
        break;
    }
  }
  std::vector<std::vector<int>> result{};
  std::vector<int> row_vec = {}; 
  for ( int row = 0; row < 9; row++ ) {
    row_vec.clear();
    for ( int col = 0; col < 9; col++ ) {
      row_vec.push_back(vec_info.at(row).at(col).current.back());
    }
    result.push_back(row_vec);
  }
  return result;
}
