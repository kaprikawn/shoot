#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "vector.hpp"
#include "structs.hpp"

class Movement {
  
  private:
  
    Vector coordinates_; // sdl position
    int w_; // width
    int h_; // height
    
  
  public:
    Movement( int x, int y, int w, int h );
    ~Movement(){}
    
    void updatePosition( Vector velocity, float dt );
    
    Vector getCoordinates() { return coordinates_; }
    Vector getSpriteCenter();
    
};

#endif //MOVEMENT_HPP
