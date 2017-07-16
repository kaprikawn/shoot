#include <iostream>
#include "position.hpp"


Position::Position( std::unique_ptr<ObjectData>& objectData ) : 
      coordinates_( objectData -> x, objectData -> y )
    , drawPosition_( 0, 0 ) {
    
  w_ = objectData -> width;
  h_ = objectData -> height;
    
  hb_l_offset_ = objectData -> hb_l_offset;
  hb_r_offset_ = objectData -> hb_r_offset;
  hb_t_offset_ = objectData -> hb_t_offset;
  hb_b_offset_ = objectData -> hb_b_offset;
  
  hb_width_ = w_ - hb_l_offset_ - hb_r_offset_;
  
}

void Position::updateHitbox( Vector &velocity ) {

  if( velocity.getX() < 0 ) {
    hitbox_.left  = x_ + ( hb_r_offset_ * scale_ );
  } else {
    hitbox_.left  = x_ + ( hb_l_offset_ * scale_ );
  }
  hitbox_.right = hitbox_.left + ( ( w_ - hb_l_offset_ - hb_r_offset_ ) * scale_ );
  hitbox_.top   = y_ + ( hb_t_offset_ * scale_ );
  hitbox_.bottom  = hitbox_.top  + ( ( h_ - hb_t_offset_ - hb_b_offset_ ) * scale_ );
}

void Position::updatePosition( Vector &velocity, float &dt, DrawFrameParams &renderParams, bool &ignoreScale, int elevation ) {

  coordinates_ = coordinates_ + velocity * dt;
  
  if( ignoreScale ) {
    scale_ = 1.0f;
  } else {
    scale_ = 0.1f + ( ( 1.0f - 0.1f ) * ( ( coordinates_.getY() + h_ ) / 720.0f ) );
  }
  if( scale_ > 1.0f ) { scale_ = 1.0f; }
  if( scale_ < 0.1f ) { scale_ = 0.1f; }
  
  x_ = coordinates_.getX() + ( scale_ * ( w_ - ( w_ * scale_ ) ) );
  y_ = coordinates_.getY() + ( scale_ * ( h_ - ( h_ * scale_ ) ) ) + elevation;
  
  renderParams.dstX = x_;
  renderParams.dstY = y_;
  renderParams.dstW = w_ * scale_;
  renderParams.dstH = h_ * scale_;
  
  Position::updateHitbox( velocity );
  
  zIndex_ = y_ + ( h_ * scale_ );
  //std::cout << "calculated zIndex is " << zIndex_ << std::endl;
  
}

Vector Position::getSpriteCenter() {
  
  return Vector( coordinates_.getX() + ( w_ / 2 ), coordinates_.getY() + ( h_ / 2 ) );
  
}
