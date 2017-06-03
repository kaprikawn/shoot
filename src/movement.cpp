#include <iostream>
#include "movement.hpp"

Movement::Movement( int x, int y ) : coordinates_( x, y ) {

}

void Movement::updatePosition( Vector velocity, float dt ) {
  coordinates_ = coordinates_ + velocity * dt;
}


