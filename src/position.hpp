#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include <memory>
#include "vector.hpp"
#include "structs.hpp"

class Position {
  
  private:
  
    Vector  coordinates_; // sdl position
    Vector  drawPosition_; // for render params
    Hitbox  hitbox_; // defined in structs
    int     w_; // width
    int     h_; // height
    float   scale_;
    
    int x_; // x of draw location for use in hitbox calculation
    int y_; // y of draw location for use in hitbox calculation
    
    // how many pixels from the edge of the sprite should the hitbox start
    // because we don't necessarily want the hitbox to be the same size as the sprite
    int hb_l_offset_ = 0; // hitbox left offset
    int hb_r_offset_ = 0; // hitbox right offset
    int hb_t_offset_ = 0; // hitbox top offset
    int hb_b_offset_ = 0; // hitbox bottom offset
    int hb_width_;
  
  public:
    Position( std::unique_ptr<ObjectData>& objectData );
    ~Position(){}
    
    void updatePosition( Vector &velocity, float &dt, DrawFrameParams &renderParams, bool &ignoreScale, int elevation );
    
    Vector  getCoordinates() { return coordinates_; }
    Hitbox  getHitbox()      { return hitbox_; }
    int     getHitboxWidth() { return hb_width_; }
    
    void    updateHitbox( Vector &velocity );
    Vector  getSpriteCenter();
    void setX( float x ) {
      coordinates_.setX( x );
    }
    void setY( float y ) {
      coordinates_.setY( y );
    }
    
};

#endif //MOVEMENT_HPP
