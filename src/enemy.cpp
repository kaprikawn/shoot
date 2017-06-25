#include <iostream>
#include "enemy.hpp"


Enemy::Enemy( std::unique_ptr<ObjectData> objectData ) : Sprite( std::move( objectData ) ), destination_( 0, 0 ) {
  
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
  
  if( pathDataIndex_ == 0 ) {
    Enemy::calculateVelocity( pathDataIndex_ );
  }
  
  if( spriteState_ == MOVING && Sprite::hasPassedDestination( srcX_, srcY_, dstX_, dstY_ ) ) {
    //recalculateVelocity_ = true;
    velocity_.setX( 0 );
    velocity_.setY( 0 );
    spriteState_ = FIRING;
  }
  
  Sprite::update( dt, msFrameDiff );
  
  if( spriteState_ == FIRING && fixedAnimDone_ ) {
    Enemy::calculateVelocity( pathDataIndex_ );
    Sprite::update( dt, msFrameDiff );
  }
  
  if( spriteState_ == DYING && fixedAnimDone_ ) {
    deleteSprite_ = true;
  }
  
}

void Enemy::render() {
  Sprite::render();
}

void Enemy::clean() {
  Sprite::clean();
}
