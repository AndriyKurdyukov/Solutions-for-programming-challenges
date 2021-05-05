#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include "snake.h"



int main(){
    Snake sn=Snake{200,200,Up,2};
    Food f= Food{i2tuple(100,200)};
    int width=400;
    int height=400;
    sf::RenderWindow window(sf::VideoMode(width, height), "Snake");
    sf::Time elapsed;
    sf::Clock clock;
    sf::Text text;
    sf::RectangleShape rect;
    
    std::vector<i2tuple> info;
 
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
              if (event.key.code == sf::Keyboard::Left)
              {
          //      std::cout << "the left key was pressed" << std::endl;
                sn.turn(Right);
              }
              if (event.key.code == sf::Keyboard::Right)
              {
               // std::cout << "the right key was pressed" << std::endl;
                sn.turn(Left);
              }

            }

        }
        // clear the window with black color
        window.clear(sf::Color::Black);
        // draw everything here...
        // window.draw(...);
        info = sn.get_vec_info();
        for(i2tuple t: info){
           rect.setSize(sf::Vector2f(10, 10));
           rect.setPosition( std::get<0>(t), std::get<1>(t));
           window.draw(rect);
        }   
        if(!f.get_status()){
          rect.setSize(sf::Vector2f(10, 10));
          rect.setPosition( std::get<0>(f.get_position()), std::get<1>(f.get_position()));
          window.draw(rect);
        }else{
          f.uneat(i2tuple(((rand()%width+1)/10)*10, ((rand()%height+1)/10)*10  ));
        }
 
        elapsed=clock.getElapsedTime();
        if(elapsed>sf::milliseconds(100)){
          sn.eat_food(f);
          sn.move_vec_forward();
          elapsed = clock.restart();
        }
        if(sn.check_collision()){
          window.clear(sf::Color::Black);
          window.close();
          std::cout<<"GAME OVER."<<std::endl;
        }
        // end the current frame
        
        window.display();
    }
  
  return 0;
}
