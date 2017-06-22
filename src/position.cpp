#include <iostream>
#include "position.hpp"

Position::Position( int x, int y, int w, int h, bool centerOffset ) : 
  //coordinates_( x - ( w / 2), y - ( h / 2 ) ) {
  coordinates_( x, y ), drawPosition_( 0, 0 ) {
  w_ = w;
  h_ = h;
  
}

void Position::updatePosition( Vector velocity, float dt, DrawFrameParams &renderParams, bool ignoreScale, int elevation ) {

  coordinates_ = coordinates_ + velocity * dt;
  
  if( ignoreScale ) {
    scale_ = 1.0f;
  } else {
    scale_ = 0.5f + ( ( 1.0f - 0.5f ) * ( ( coordinates_.getY() + h_ ) / 720.0f ) );
  }
  if( scale_ > 1.0f ) { scale_ = 1.0f; }
  if( scale_ < 0.5f ) { scale_ = 0.5f; }
  
  renderParams.dstX = coordinates_.getX() + ( scale_ * ( w_ - ( w_ * scale_ ) ) );
  renderParams.dstY = coordinates_.getY() + ( scale_ * ( h_ - ( h_ * scale_ ) ) ) + elevation;
  renderParams.dstW = w_ * scale_;
  renderParams.dstH = h_ * scale_;
  
}

Vector Position::getSpriteCenter() {
  
  return Vector( coordinates_.getX() + ( w_ / 2 ), coordinates_.getY() + ( h_ / 2 ) );
  
}
