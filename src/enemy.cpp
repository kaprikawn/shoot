#include <iostream>
#include "enemy.hpp"


Enemy::Enemy( ObjectData* objectData ) : Sprite( objectData ), destination_( 0, 0 ) {
  
}

void Enemy::calculateVelocity( int pathDataIndex ) {

  srcX_ = position_.getCoordinates().getX();
  srcY_ = position_.getCoordinates().getY();
  dstX_ = objectData_ -> pathData[ pathDataIndex_ ].x;
  dstY_ = objectData_ -> pathData[ pathDataIndex_ ].y;
  
  destination_.setX( dstX_ );
  destination_.setY( dstY_ );
  
  velocity_ = destination_ - position_.getCoordinates();
  
  velocity_.normalize();
  velocity_ *= objectData_ -> speed;
  if( pathDataIndex_ > 0 ) {
    spawnProjectile_ = EBOMB;
  }
  
  // if the projectile is going more horizontally than vertically
  // test whether it has passed the target based on X coordinates, otherwise default Y
  if( abs( dstY_ - srcY_ ) < abs( dstX_ - srcY_ ) ) {
    testOnY_ = false;
  } else {
    testOnY_ = true;
  }
  
  spriteState_ = MOVING;
  
  pathDataIndex_++;
  recalculateVelocity_ = false;
  
}

void Enemy::update( float dt, Uint32 msFrameDiff ) {
  
  if( Sprite::hasPassedDestination( srcX_, srcY_, dstX_, dstY_ ) ) {
    recalculateVelocity_ = true;
  }
  
  if( recalculateVelocity_ ) {
    Enemy::calculateVelocity( pathDataIndex_ );
  }
  
  Sprite::update( dt, msFrameDiff );
  
}

void Enemy::render() {
  Sprite::render();
}

void Enemy::clean() {

}
