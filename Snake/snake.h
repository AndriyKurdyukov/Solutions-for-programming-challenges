#pragma once
#include <vector>
#include <tuple>
#include "food.h"

enum direction{
     Left,
     Up,
     Right,
     Down
     };

struct info{
  int x;
  int y;
  direction dir;
};

typedef std::tuple<int,int> i2tuple;

class Snake{
  private:   
    int x;
    int y;
    direction dir;
    int len;
    int size; //size of one square
    std::array<i2tuple,4> arr_points;
    std::array<i2tuple,3> old_points;

    std::vector<i2tuple> vec_points;
    std::vector<i2tuple> old_vec_points;

  public:
    
    Snake(int X, int Y, direction Dir, int length); //snake of given length
    void print();
    void move_forward();
    void move_vec_forward();
    void turn(direction Dir);
    std::array<i2tuple,4> get_info();
    std::vector<i2tuple> get_vec_info();
    void eat_food(Food& f);
    void grow();
    bool check_collision();

};
