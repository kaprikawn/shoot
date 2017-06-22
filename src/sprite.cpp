#include <iostream>
#include "sprite.hpp"
#include "textures.hpp"
#include "game.hpp"

Sprite::Sprite( ObjectData* objectData ) : 
    health_( objectData -> hp )
  , position_( objectData -> x, objectData -> y, objectData -> width, objectData -> height, objectData -> centerOffset )
  , velocity_( 0, 0 )
  , animation_( objectData -> stateData )
  , elevationP_( 0, 0 )
  , elevationV_( 0, 0 )
  , elevationG_( 0, 0 )
   {
  
  objectData_ = objectData;
  
  renderParams_.id = objectData -> textureID;
  renderParams_.srcW = objectData -> width;
  renderParams_.srcH = objectData -> height;
  
}

bool Sprite::hasPassedDestination( int srcX, int srcY, int dstX, int dstY ) {
  
  if( testOnY_ ) {
    if( dstY <= srcY && position_.getCoordinates().getY() <= dstY ) {
      return true;
    } else if( dstY >= srcY && position_.getCoordinates().getY() >= dstY ) {
      return true;
    }
  } else {
    if( dstX >= srcX && position_.getCoordinates().getX() >= dstX ) {
      return true;
    } else if( dstX <= srcX && position_.getCoordinates().getX() <= dstX ) {
      return true;
    }
  }
  return false;
}

void Sprite::update( float dt, Uint32 mfFrameDiff ) {

  elevationP_ = elevationP_ + elevationV_ * dt;
  elevationV_ = elevationV_ + elevationG_ * dt;
  
  elevation_ = elevationP_.getY();
  if( elevation_ > 0.0f ) { elevation_ = 0.0f; }
  
  position_.updatePosition( velocity_, dt, renderParams_, ignoreScale_, elevation_ );
  
  drawIndex_ = position_.getCoordinates().getY() + objectData_ -> height;
  
  if( velocity_.getX() < 0 ) {
    renderParams_.flip = true;
  } else {
    renderParams_.flip = false;
  }
  
  // determine current animation frame
  // returns true if sprite was in a fixed animation that is now finished
  fixedAnimDone_ = animation_.determineFrame( spriteState_, dt, mfFrameDiff
    , renderParams_.currentFrame
    , renderParams_.currentRow
  );
  
}

void Sprite::render() {
  TheTextures::Instance() -> drawFrame( renderParams_ );
}



void Sprite::clean() {
  
}
