#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "vector.hpp"
#include "structs.hpp"

class Position {
  
  private:
  
    Vector coordinates_; // sdl position
    Vector drawPosition_; // for render params
    //Vector hitbox_; // hitbox start x / y
    int w_; // width
    int h_; // height
    float scale_;
    
    int renderW_; // render width
    int renderH_; // render height
    
  
  public:
    Position( int x, int y, int w, int h, bool centerOffset );
    ~Position(){}
    
    void updatePosition( Vector velocity, float dt, DrawFrameParams &renderParams, bool ignoreScale, int elevation );
    
    Vector getCoordinates() { return coordinates_; }
    Vector getSpriteCenter();
    
    void setX( float x ) {
      coordinates_.setX( x );
    }
    void setY( float y ) {
      coordinates_.setY( y );
    }
    
};

#endif //MOVEMENT_HPP
