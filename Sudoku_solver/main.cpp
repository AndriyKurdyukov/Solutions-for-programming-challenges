#include <iostream>
#include <fstream>
#include <string>
#include "sudoku.h"

void tokenize(std::string str, int (&arr)[9][9], int row   ) {
  std::string token{};
  int n = 0;
  int col = 0;
  while ( str.find(',') < str.length() ) {
    str = str.substr(n, str.length()-n);
    n = str.find(',');
    token = str.substr(0, n);
    n++;
    arr[row][col]= (int)(token[0]-48);
    col++;
  }
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>.txt" << std::endl;
    return 1;
    }
  std::ifstream myfile;
  std::string line;
  myfile.open(argv[1]);
  int arr1[9][9]{};
  int n = 0;
  int row = 0;
  if ( myfile.is_open() ) {
    while ( std::getline (myfile, line) ) {
      tokenize(line, arr1, row);
      row++;
    }
  }
  Sudoku sud = Sudoku {arr1};
  auto solution = sud.solve_sudoku();
  for ( int row = 0; row < 9; row++ ) {
    for ( int col = 0; col < 9; col++ ) {
      std::cout << solution.at(row).at(col);
      if (col < 8) std::cout << ",";
    }
    std::cout << std::endl;
  }
}
