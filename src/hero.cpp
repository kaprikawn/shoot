#include <iostream>
#include "hero.hpp"
#include "inputHandler.hpp"

Hero::Hero( ObjectData* objectData ) : Sprite( objectData ) {
  
}

void Hero::handleInput() {
  if( spriteState_ != DODGING ) {
    if( TheInputHandler::Instance() -> isPressed( RIGHT ) ) {
      spriteState_ = MOVING;
      velocity_.setX( 200 );
    } else if( TheInputHandler::Instance() -> isPressed( LEFT ) ) {
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
