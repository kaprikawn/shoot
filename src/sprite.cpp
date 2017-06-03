#include <iostream>
#include "sprite.hpp"
#include "textures.hpp"
#include "game.hpp"

Sprite::Sprite( ObjectData* objectData ) : health_( objectData -> hp ) {
  objectData_ = objectData;
  
  renderParams_.id = objectData -> textureID;
  renderParams_.w = objectData -> width;
  renderParams_.h = objectData -> height;
  
}

void Sprite::update( float dt, Uint32 mfFrameDiff ) {

}

void Sprite::render() {
  
  renderParams_.x = 200;
  renderParams_.y = 380;
  renderParams_.scale = 1.0f;
  renderParams_.currentRow = 1;
  renderParams_.currentFrame = 0;
  renderParams_.flip = false;


  TheTextures::Instance() -> drawFrame( renderParams_ );
}

void Sprite::clean() {
  
}
