#include <iostream>
#include "target.hpp"
#include "inputHandler.hpp"
#include "structs.hpp"

Target::Target( std::unique_ptr<ObjectData> objectData ) : Sprite( std::move( objectData ) ) {
  ignoreScale_    = true;
}

void Target::handleInput() {
  
  if( TheInputHandler::Instance() -> isPressed( FIRE ) ) {
    spriteState_ = FIRING;
    hostileToEnemy_ = true;
  } else {
    spriteState_ = DEFAULT;
    hostileToEnemy_ = false;
  }
  
  if( TheInputHandler::Instance() -> isPressed( RIGHT ) && position_.getCoordinates().getX() < 1280 - objectData_ -> width ) {
    if( spriteState_ == FIRING ) {
      velocity_.setX( 250 );
    } else {
      velocity_.setX( 400 );
    }
  } else if( TheInputHandler::Instance() -> isPressed( LEFT ) && position_.getCoordinates().getX() > 0 ) {
    if( spriteState_ == FIRING ) {
      velocity_.setX( -250 );
    } else {
      velocity_.setX( -400 );
    }
  } else {
    velocity_.setX( 0 );
  }
  
  if( TheInputHandler::Instance() -> isPressed( DOWN ) && position_.getCoordinates().getY() < 720 - objectData_ -> height ) {
    if( spriteState_ == FIRING ) {
      velocity_.setY( 250 );
    } else {
      velocity_.setY( 400 );
    }
    
  } else if( TheInputHandler::Instance() -> isPressed( UP ) && position_.getCoordinates().getY() > 0 ) {
    if( spriteState_ == FIRING ) {
      velocity_.setY( -250 );
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
