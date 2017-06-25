#include <iostream>
#include "sprite.hpp"
#include "textures.hpp"
#include "game.hpp"
#include "SDL.h"

Sprite::Sprite( std::unique_ptr<ObjectData> objectData ) : 
    health_( objectData -> hp )
  , position_( objectData )
  , velocity_( 0, 0 )
  , animation_( objectData -> stateData )
  , elevationP_( 0, 0 )
  , elevationV_( 0, 0 )
  , elevationG_( 0, 0 )
   {
   
  objectData_ = std::move( objectData );
  
  renderParams_.id        = objectData_ -> textureID;
  renderParams_.srcW      = objectData_ -> width;
  renderParams_.srcH      = objectData_ -> height;
  
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
  bottomY_ = drawIndex_;
  
  if( velocity_.getX() < 0 ) {
    renderParams_.flip = true;
  } else {
    renderParams_.flip = false;
  }
  
  if( health_.getCurrentHp() < 1 ) {
    spriteState_ = DYING;
    velocity_.setX( 0 );
    velocity_.setY( 0 );
  }
  
  // determine current animation frame
  // returns true if sprite was in a fixed animation that is now finished
  fixedAnimDone_ = animation_.determineFrame( spriteState_, dt, mfFrameDiff
    , renderParams_.currentFrame
    , renderParams_.currentRow
  );
  
}

void Sprite::reduceHp( int attackAmount ) {
  if( spriteState_ == DYING || spriteState_ == DODGING ) { return; }
  
  health_.reduceHp( attackAmount );
  
}

void Sprite::render() {
  
  renderParams_.spriteID  = objectData_ -> spriteID;
  
  TheTextures::Instance() -> drawFrame( renderParams_ );
  
    
  if( showHitbox_ ) {
    SDL_SetRenderDrawColor(TheGame::Instance() -> getRenderer(), 255, 0, 0, 255);
    SDL_Rect rectangle;
    
    Hitbox myHitbox = position_.getHitbox();

    rectangle.x = myHitbox.left;
    rectangle.y = myHitbox.top;
    rectangle.w = myHitbox.right - myHitbox.left;
    rectangle.h = myHitbox.bottom - myHitbox.top;
    SDL_RenderDrawRect(TheGame::Instance() -> getRenderer(), &rectangle);
  }
  
}

void Sprite::clean() {

}
