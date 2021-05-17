#pragma once
#include <stack>
#include <vector>
#include <cassert>

typedef struct info {  // information about each cell
  bool is_chosen;  // is the first number candidate currently chosen
  bool is_given;  // this cell is given from the start
  std::vector<int>  current;  // current number candidates for each cell
  std::vector<int>  start;  // starting number candidates for each cell
} inf;

class Sudoku{
  std::vector<std::vector<inf>> vec_info;  // vector of infos for each cell;
  void fill_candidates(int row, int col, std::vector<std::vector<inf>>& vec);
  // param1 0 for row, param1 1 for col. param2 0 for given, 1 for chosen
  std::vector<int> check_row(int row, std::vector<std::vector<inf>> vec, bool param1, bool given_or_chosen);
  // return numbers for a 3x3 box
  std::vector<int> check_box(int row, int col, std::vector<std::vector<inf>> vec, bool given_or_chosen);     
 public:
  Sudoku(int input[9][9]);
  std::vector<int> set_op(std::vector<int> set1, std::vector<int> set2, bool param);
  std::vector<std::vector<int>> solve_sudoku();
  friend void test();
};
