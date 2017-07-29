#include <iostream>
#include "scenary.hpp"
#include "inputHandler.hpp"
#include "structs.hpp"

Scenary::Scenary( std::unique_ptr<ObjectData> objectData ) : Sprite( std::move( objectData ) ) {
  ignoreScale_    = true;
}

void Scenary::update( float dt, Uint32 msFrameDiff ) {
  Sprite::update( dt, msFrameDiff );
  
  //std::cout << "scenary zIndex is " << zIndex_ << std::endl;
  
}

void Scenary::render() {
  Sprite::render();
}

void Scenary::clean() {

}
