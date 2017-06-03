#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "vector.hpp"
#include "structs.hpp"

class Movement {
  
  private:
  
    Vector coordinates_; // sdl position
    
  
  public:
    Movement( int x, int y );
    ~Movement(){}
    
    void updatePosition( Vector velocity, float dt );
    
    Vector getCoordinates() { return coordinates_; }
    
};

#endif //MOVEMENT_HPP
