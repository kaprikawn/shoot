#include <iostream>
#include "scenary.hpp"
#include "inputHandler.hpp"
#include "structs.hpp"

Scenary::Scenary( std::unique_ptr<ObjectData> objectData ) : Sprite( std::move( objectData ) ) {
  ignoreScale_    = true;
}

void Scenary::update( float dt, Uint32 msFrameDiff ) {
  
  if( health_.getCurrentHp() < health_.getMaxHp() ) {
    if( health_.getCurrentHp() < 260 ) {
      spriteState_ = DAMAGED3;
    } else if( health_.getCurrentHp() < 510 ) {
      spriteState_ = DAMAGED2;
    } else if( health_.getCurrentHp() < 760 ) {
      spriteState_ = DAMAGED1;
    }
  }
  
  Sprite::update( dt, msFrameDiff );
  
  //std::cout << "scenary zIndex is " << zIndex_ << std::endl;
  
}

void Scenary::render() {
  Sprite::render();
}

void Scenary::clean() {

}
