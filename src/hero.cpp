#include <iostream>
#include "hero.hpp"
#include "inputHandler.hpp"
#include "values.hpp"

Hero::Hero( std::unique_ptr<ObjectData> objectData ) : Sprite( std::move( objectData ) ) {
  ignoreScale_ = true;
}

void Hero::handleInput() {

  if( startupDelay_ > 0 ) {
    startupDelay_--;
    return;
  }
  
  spawnProjectile_ = 0;
  
  if( spriteState_ == DYING ) { return; }
  
  if( spriteState_ == MOVING || spriteState_ == FIRING || spriteState_ == DEFAULT ) {
    
    if( TheInputHandler::Instance() -> isPressed( DODGE ) ) {
      spriteState_ = DODGING;
    } else if( TheInputHandler::Instance() -> isPressed( BOMB ) && bombCooldown_ > 1000 && TheValues::Instance() -> getBombs() > 0 ) {
      spawnProjectile_ = PBOMB;
      TheValues::Instance() -> updateBombs( -1 );
      bombCooldown_ = 0;
    } else if( TheInputHandler::Instance() -> isPressed( FIRE ) ) {
      spriteState_ = FIRING;
      if( bulletCooldown_ > 100 ) {
        spawnProjectile_ = PBULLET;
        bulletCooldown_ = 0;
      }
    } else {
      spriteState_ = DEFAULT;
    }
  }
  
  if( spriteState_ == DODGING ) {
    if( lastDirection_ == DIR_LEFT ) {
      velocity_.setX( -150 );
    } else {
      velocity_.setX( 150 );
    }
  } else if( spriteState_ == FIRING ) {
    velocity_.setX( 0 );
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
  health_.cycleInvCounter( msFrameDiff );
  invCounter_ = health_.getInvCounter();
  
  if( position_.getCoordinates().getX() >= 1279 - objectData_ -> width && velocity_.getX() > 0 ) {
    velocity_.setX( 0 );
    if( spriteState_ == MOVING ) {
      spriteState_ = DEFAULT;
    }
  } else if( position_.getCoordinates().getX() <= 1 && velocity_.getX() < 0 ) {
    velocity_.setX( 0 );
    if( spriteState_ == MOVING ) {
      spriteState_ = DEFAULT;
    }
  }
  
  Sprite::update( dt, msFrameDiff );
  
  if( fixedAnimDone_ ) {
    //std::cout << "hero currentRow is " << renderParams_.currentRow << std::endl;
    
    if( spriteState_ == DYING ) {
      TheValues::Instance() -> updateLives( -1 );
      // if gameover
      health_.setHp( 1 );
      health_.setInvCounter( 5000 );
      //printf( "finished dying\n" );
    } else if( spriteState_ == DODGING ) {
      health_.setInvCounter( 200 );
    }
    spriteState_ = DEFAULT;
    Hero::handleInput();
    
    Sprite::update( 0, 0 );
    //printf( "sprite state is now %d\n", spriteState_ );
  }
  
  bombCooldown_   += msFrameDiff;
  bulletCooldown_ += msFrameDiff;
  
}

void Hero::render() {
  Sprite::render();
}

void Hero::clean() {

}
