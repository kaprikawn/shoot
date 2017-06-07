#include <iostream>
#include "target.hpp"
#include "inputHandler.hpp"
#include "structs.hpp"

Target::Target( ObjectData* objectData ) : Sprite( objectData ) {
  
  ignoreScale_   = true;
  
}

void Target::handleInput() {
  
  if( TheInputHandler::Instance() -> isPressed( FIRE ) ) {
    spriteState_ = FIRING;
  } else {
    spriteState_ = DEFAULT;
  }
  
  if( TheInputHandler::Instance() -> isPressed( RIGHT ) && movement_.getCoordinates().getX() < 1280 - objectData_ -> width ) {
    if( spriteState_ == FIRING ) {
      velocity_.setX( 150 );
    } else {
      velocity_.setX( 400 );
    }
  } else if( TheInputHandler::Instance() -> isPressed( LEFT ) && movement_.getCoordinates().getX() > 0 ) {
    if( spriteState_ == FIRING ) {
      velocity_.setX( -150 );
    } else {
      velocity_.setX( -400 );
    }
  } else {
    velocity_.setX( 0 );
  }
  
  if( TheInputHandler::Instance() -> isPressed( DOWN ) && movement_.getCoordinates().getY() < 720 - objectData_ -> height ) {
    if( spriteState_ == FIRING ) {
      velocity_.setY( 150 );
    } else {
      velocity_.setY( 400 );
    }
    
  } else if( TheInputHandler::Instance() -> isPressed( UP ) && movement_.getCoordinates().getY() > 0 ) {
    if( spriteState_ == FIRING ) {
      velocity_.setY( -150 );
    } else {
      velocity_.setY( -400 );
    }
  } else {
    velocity_.setY( 0 );
  }
}

void Target::update( float dt, Uint32 msFrameDiff ) {

  Target::handleInput();
  Sprite::update( dt, msFrameDiff );
  
}

void Target::render() {
  Sprite::render();
}

void Target::clean() {

}
