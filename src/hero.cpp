#include <iostream>
#include "hero.hpp"
#include "inputHandler.hpp"

Hero::Hero( ObjectData* objectData ) : Sprite( objectData ) {
  ignoreScale_ = true;
}

void Hero::handleInput() {

  if( spriteState_ == DYING ) { return; }
  
  if( spriteState_ == MOVING || spriteState_ == FIRING || spriteState_ == DEFAULT ) {
    if( TheInputHandler::Instance() -> isPressed( DODGE ) ) {
      spriteState_ = DODGING;
    }
  }
  
  if( spriteState_ == DODGING ) {
    if( lastDirection_ == DIR_LEFT ) {
      velocity_.setX( -150 );
    } else {
      velocity_.setX( 150 );
    }
  } else {
    if( TheInputHandler::Instance() -> isPressed( RIGHT ) ) {
      spriteState_ = MOVING;
      velocity_.setX( 200 );
      lastDirection_ = DIR_RIGHT;
    } else if( TheInputHandler::Instance() -> isPressed( LEFT ) ) {
      spriteState_ = MOVING;
      velocity_.setX( -200 );
      lastDirection_ = DIR_LEFT;
    } else {
      spriteState_ = DEFAULT;
      velocity_.setX( 0 );
    }
  }
}

void Hero::update( float dt, Uint32 msFrameDiff ) {
  
  Hero::handleInput();
  
  if( movement_.getCoordinates().getX() >= 1279 - objectData_ -> width && velocity_.getX() > 0 ) {
    velocity_.setX( 0 );
  } else if( movement_.getCoordinates().getX() <= 1 && velocity_.getX() < 0 ) {
    velocity_.setX( 0 );
  }
  
  Sprite::update( dt, msFrameDiff );
  
  if( fixedAnimDone_ ) {
    spriteState_ = DEFAULT;
    Hero::handleInput();
    Sprite::update( dt, msFrameDiff );
  }
}

void Hero::render() {
  Sprite::render();
}

void Hero::clean() {

}
