#include <iostream>
#include "movement.hpp"

Movement::Movement( int x, int y, int w, int h ) : 
  coordinates_( x - ( w / 2), y - ( h / 2 ) ) {
  w_ = w;
  h_ = h;
}

void Movement::updatePosition( Vector velocity, float dt ) {
  coordinates_ = coordinates_ + velocity * dt;
}

Vector Movement::getSpriteCenter() {
  
  return Vector( coordinates_.getX() + ( w_ / 2 ), coordinates_.getY() + ( h_ / 2 ) );
  
}
