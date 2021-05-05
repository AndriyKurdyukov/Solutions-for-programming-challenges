#pragma once
#include <vector>
#include <tuple>



typedef std::tuple<int,int> i2tuple;

class Food{
  private:
    i2tuple position;
    bool eaten;
  public:
    Food(i2tuple pos){
      position=pos;
      eaten=false;
    }

    void get_eaten(){
      eaten=true;
     // std::cout<<"eaten!"<<std::endl;
    }
    i2tuple get_position(){
      return position;
    }
    bool get_status(){
      return eaten;
    }
    void uneat(i2tuple pos){
     // std::cout<< std::get<0>(pos)<<"__"<<std::get<1>(pos)<<std::endl;
      position=pos;
      eaten=false;
    }

};
