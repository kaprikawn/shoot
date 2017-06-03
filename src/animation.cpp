#include <iostream>
#include "animation.hpp"
#include "structs.hpp"

Animation::Animation() {

}

bool Animation::determineFrame( int spriteState, float dt, Uint32 mfFrameDiff
    , int& currentFrame
    , int& currentRow
    , float& scale
  ) {
  
    msSinceLastChange_ += mfFrameDiff;
    
    if( spriteState == DEFAULT ) {
      currentFrame = 0;
    } else {
      if( msSinceLastChange_ > frameDuration_ ) {
        currentFrame++;
        msSinceLastChange_ = 0;
        if( currentFrame > 9 || currentFrame < 2 ) {
          currentFrame = 2;
        }
      }
    }
    
    
    currentRow = 1;
    scale = 1.0f;
  
  return true;
}

