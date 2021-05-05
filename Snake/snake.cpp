#include <iostream>
#include "snake.h"
#include "food.h"


    Snake::Snake(int X, int Y, direction Dir, int length){  //constructor for snake of var. size
      vec_points.reserve(20);
      dir = Dir;
      size=10;  //rectangle size
      int i=0;
      len=length;
      switch(dir){
      case Up:
          //create parts of a snake 
        i=0;
        while(i < length){
          vec_points.push_back(i2tuple(X,Y-i*size));
          old_vec_points.push_back(i2tuple(X,Y-i*size));
          i++;
        }
        break;
      case Down:
        i=0;
        while(i < length){
          vec_points.push_back(i2tuple(X,Y+i*size));
          old_vec_points.push_back(i2tuple(X,Y+i*size));
          i++;
        }
        break; 
      case Right:
        i=0;
        while(i < length){
          vec_points.push_back(i2tuple(X-i*size,Y));
          old_vec_points.push_back(i2tuple(X-i*size,Y));
          i++;
        }
        break; 
      case Left:
        i=0;
        while(i < length){
          vec_points.push_back(i2tuple(X+i*size,Y));
          old_vec_points.push_back(i2tuple(X+i*size,Y));
          i++;
        }
        break; 
      }
     

    }

    void Snake::print(){
     std::cout<<"dir:"<<dir<<std::endl;
     for(i2tuple t: arr_points){
      std::cout << std::get<0>(t) << ' ';
      std::cout << std::get<1>(t) << '\n';
     }
    }
    
    std::array<i2tuple,4> Snake::get_info(){
      return arr_points;
    }

    std::vector<i2tuple> Snake::get_vec_info(){
      return vec_points;
    }

    void Snake::move_forward(){
      old_points.at(0)=arr_points.at(0);
      old_points.at(1)=arr_points.at(1);
      old_points.at(2)=arr_points.at(2);
      switch(dir){
      case Up:
        y++;
        std::get<1>(arr_points.at(0))=std::get<1>(arr_points.at(0))+size;
        break;
      case Down:
        y--;
        std::get<1>(arr_points.at(0))=std::get<1>(arr_points.at(0))-size;
        break;
      case Right:
        x=x+1;
        std::get<0>(arr_points.at(0))=std::get<0>(arr_points.at(0))+size;
        break;
      case Left:
        x=x-1;
        std::get<0>(arr_points.at(0))=std::get<0>(arr_points.at(0))-size;
        break;
      }
      arr_points.at(1)= old_points.at(0);
      arr_points.at(2)= old_points.at(1);
      arr_points.at(3)= old_points.at(2);
    }
  
    void Snake::move_vec_forward(){
      int i=0;
      while (i<len-1){
        old_vec_points[i]=vec_points[i];  //backup old points
        i++;
      }

      switch(dir){
        case Up:
          y++;
          std::get<1>(vec_points.at(0))=std::get<1>(vec_points.at(0))+size;
          break;
        case Down:
          y--;
          std::get<1>(vec_points.at(0))=std::get<1>(vec_points.at(0))-size;
          break;
        case Right:
          x=x+1;
          std::get<0>(vec_points.at(0))=std::get<0>(vec_points.at(0))+size;
          break;
        case Left:
          x=x-1;
          std::get<0>(vec_points.at(0))=std::get<0>(vec_points.at(0))-size;
          break;
        }
      
      i=0;
      while (i < len-1){
        vec_points[i+1]=old_vec_points[i];  //update
        i++;
      }
 
      }
    void Snake::grow(){
      i2tuple last=vec_points.at(len-1);
      i2tuple blast=vec_points.at(len-2);
      int dx=std::get<0>(last)-std::get<0>(blast);
      int dy=std::get<1>(last)-std::get<1>(blast);
      vec_points.push_back(i2tuple(std::get<0>(last)+dx,std::get<1>(last)+dy));
      len++;
    }

    void Snake::eat_food(Food& f){
      i2tuple pos= f.get_position();
      int X=std::get<0>(vec_points.at(0));
      int Y=std::get<1>(vec_points.at(0));
      if((X==std::get<0>(pos)) and (Y==std::get<1>(pos))){
        f.get_eaten();   //eat food
        grow();
      }
        
    }

    void Snake::turn(direction Dir){
      switch(Dir){
        case Up:
          break;
        case Down:
          break;
        case Right:
          switch(dir){
            case Left:
              dir=Up;
              break;
            case Right:
              dir=Down;
              break;
            case Up:
              dir=Right;
              break;
            case Down:
              dir=Left;
              break;
          }
          break;
          
        case Left:
           switch(dir){
            case Left:
              dir=Down;
              break;
            case Right:
              dir=Up;
              break;
            case Up:
              dir=Left;
              break;
            case Down:
              dir=Right;
              break;
          }
          break;
      }
    }

    bool Snake::check_collision(){

      bool b1=std::get<0>(vec_points.at(0)) > 400;
      bool b2=std::get<0>(vec_points.at(0)) < 0;
      bool b3=std::get<1>(vec_points.at(0)) > 400;
      bool b4=std::get<1>(vec_points.at(0)) < 0;

      if(b1 or b2 or b3 or b4){
        return true;
      }
      return false;
    }


  

