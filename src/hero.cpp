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

  if( spriteState_ != DODGING ) {
    if( TheInputHandler::Instance() -> isPressed( RIGHT ) && movement_.getCoordinates().getX() < 1280 - objectData_ -> width ) {
      spriteState_ = MOVING;
      velocity_.setX( 200 );
    } else if( TheInputHandler::Instance() -> isPressed( LEFT ) && movement_.getCoordinates().getX() > 0 ) {
      spriteState_ = MOVING;
      velocity_.setX( -200 );
    } else {
      spriteState_ = DEFAULT;
      velocity_.setX( 0 );
    }
  }
}

void Hero::update( float dt, Uint32 msFrameDiff ) {

  
  Hero::handleInput();
  
  Sprite::update( dt, msFrameDiff );
}

void Hero::render() {
  Sprite::render();
}

void Hero::clean() {

}
