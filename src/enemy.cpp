#include <iostream>
#include "enemy.hpp"


Enemy::Enemy( ObjectData* objectData ) : Sprite( objectData ), destination_( 0, 0 ) {
  std::cout << "initial x is " << objectData -> x << std::endl;
}

void Enemy::calculateVelocity( int pathDataIndex ) {
  
  destination_.setX( objectData_ -> pathData[ pathDataIndex_ ].x );
  destination_.setY( objectData_ -> pathData[ pathDataIndex_ ].y );
  
  velocity_ = destination_ - movement_.getCoordinates();
  
  velocity_.normalize();
  velocity_ *= objectData_ -> speed;
  if( pathDataIndex_ > 0 ) {
    spawnProjectile_ = true;
  }
  
  spriteState_ = MOVING;
  
  pathDataIndex_++;
  recalculateVelocity_ = false;
  
  std::cout << "current x is " << movement_.getCoordinates().getX() << std::endl;
}

void Enemy::update( float dt, Uint32 msFrameDiff ) {
  
  if( recalculateVelocity_ ) {
    Enemy::calculateVelocity( pathDataIndex_ );
  }
  
  Sprite::update( dt, msFrameDiff );
  
  //std::cout << "enemy draw index is " << drawIndex_ << std::endl;
}

void Enemy::render() {
  Sprite::render();
}

void Enemy::clean() {

}
