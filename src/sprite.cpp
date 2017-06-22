#include <iostream>
#include "sprite.hpp"
#include "textures.hpp"
#include "game.hpp"

Sprite::Sprite( ObjectData* objectData ) : 
    health_( objectData -> hp )
  , movement_( objectData -> x, objectData -> y, objectData -> width, objectData -> height )
  , velocity_( 0, 0 )
  , animation_( objectData -> stateData )
  , elevationP_( 0, 0 )
  , elevationV_( 0, 0 )
  , elevationG_( 0, 0 )
   {
  
  objectData_ = objectData;
  
  renderParams_.id = objectData -> textureID;
  renderParams_.w = objectData -> width;
  renderParams_.h = objectData -> height;
  
}

void Sprite::update( float dt, Uint32 mfFrameDiff ) {
  
  movement_.updatePosition( velocity_, dt );
  
  //std::cout << "height is " << objectData_ -> height << std::endl;
  //std::cout << "new y is " << movement_.getCoordinates().getY() << std::endl;
  
  drawIndex_ = movement_.getCoordinates().getY() + objectData_ -> height;
  
  //std::cout << "drawIndex_ is " << drawIndex_ << std::endl;
  
  elevationP_ = elevationP_ + elevationV_ * dt;
  elevationV_ = elevationV_ + elevationG_ * dt;
  
  float elevation = elevationP_.getY();
  if( elevation > 0.0f ) { elevation = 0.0f; }
  renderParams_.elevation = elevation;
  
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
    , renderParams_.scale
  );
  
}

void Sprite::render() {
  
  renderParams_.x = movement_.getCoordinates().getX();
  renderParams_.y = movement_.getCoordinates().getY();

  TheTextures::Instance() -> drawFrame( renderParams_ );
}

void Sprite::clean() {
  
}
