#include <iostream>
#include "SDL.h"
#include "enemy.hpp"
#include "game.hpp"
#include "values.hpp"

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
    spawnProjectile_ = ( *objectData_ ).projectileType;
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
  
  if( spriteState_ == DYING && !pointsAwarded_ ) {
    TheValues::Instance() -> updatePoints( health_.getMaxHp() );
    pointsAwarded_ = true;
  }
  
}

void Enemy::renderLifebar() {
  
  yellowWidth_ = objectData_ -> width * ( health_.getCurrentHp() / (float)health_.getMaxHp() );
  redWidth_ = objectData_ -> width - yellowWidth_;
  
  SDL_SetRenderDrawColor( TheGame::Instance() -> getRenderer(), 255, 255, 0, 255 );
  SDL_Rect yellow;
  yellow.x = position_.getCoordinates().getX();
  yellow.y = position_.getCoordinates().getY() - 10;
  yellow.w = yellowWidth_;
  yellow.h = 3;
  SDL_RenderFillRect( TheGame::Instance() -> getRenderer(), &yellow );
  
  SDL_SetRenderDrawColor( TheGame::Instance() -> getRenderer(), 255, 0, 0, 255 );
  SDL_Rect red;
  red.x = yellow.x + yellow.w + 1;
  red.y = yellow.y;
  red.w = redWidth_;
  red.h = yellow.h;
  SDL_RenderFillRect( TheGame::Instance() -> getRenderer(), &red );
}

void Enemy::render() {
  
  if( health_.getCurrentHp() < health_.getMaxHp() && health_.getCurrentHp() > 0 ) {
    renderLifebar();
  }
  
  Sprite::render();
}

void Enemy::clean() {
  Sprite::clean();
}
