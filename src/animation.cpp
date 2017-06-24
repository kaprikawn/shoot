#include <iostream>
#include "animation.hpp"
#include "structs.hpp"

Animation::Animation( std::vector<StateData>& stateData ) {
  stateData_ = stateData; // copy the state data from the objectData loaded in by json
}

void Animation::changeState( int newSpriteState ) {
  animationData_.clear();
  
  //printf( "changing to state %d\n", newSpriteState );
  
  for( unsigned int i = 0; i < stateData_.size(); i++ ) {
    if( stateData_[i].spriteState == newSpriteState ) {
      fixedAnim_ = stateData_[i].fixedAnim;
      currentRow_ = stateData_[i].currentRow;
      for( unsigned int a = 0; a < stateData_[i].animData.size(); a++ ) {
        animationData_.push_back( stateData_[i].animData[a] );
      }
      lastSpriteState_ = newSpriteState;
      return;
    }
  }
}

bool Animation::determineFrame( int spriteState, float dt, Uint32 mfFrameDiff
    , int& currentFrame
    , int& currentRow
  ) {
  
  msSinceLastChange_ += mfFrameDiff;
  frameNum_ = currentFrame;
  
  changeFrame_ = returnVar_ = false;
  if( animationData_.empty() || spriteState != lastSpriteState_ ) {
    Animation::changeState( spriteState );
    currentRow = currentRow_;
    currentIndex_ = 0;
  }
  
  if( fixedAnim_ && msSinceLastChange_ > animationData_[ currentIndex_ ].duration ) {
    currentIndex_++;
    if( currentIndex_ >= animationData_.size() ) {
      returnVar_ = true; // tell calling function that fixed animation has finished
    }
    msSinceLastChange_ = 0;
    changeFrame_ = true;
  } else if( msSinceLastChange_ > animationData_[ currentIndex_ ].duration ) {
    changeFrame_ = true;
    msSinceLastChange_ = 0;
  } else if( spriteState != lastSpriteState_ ) {
    changeFrame_ = true;
    //currentIndex_ = 0;
  }
  
  if( changeFrame_ ) {
    if( animationData_[ currentIndex_ ].oscillate ) {
      if( frameStep_ == 1 && frameNum_ == animationData_[ currentIndex_ ].maxFrame ) {
        frameStep_ = -1;
      } else if( frameStep_ == -1 && frameNum_ == animationData_[ currentIndex_ ].minFrame ) {
        frameStep_ = 1;
      }
    }
    frameNum_ += frameStep_;
    
  }
  
  if( frameNum_ > animationData_[ currentIndex_ ].maxFrame ) {
    frameNum_ = animationData_[ currentIndex_ ].minFrame;
  }
  
  if( frameNum_ < animationData_[ currentIndex_ ].minFrame || frameNum_ < 0 ) {
    frameNum_ = animationData_[ currentIndex_ ].minFrame;
  }
  
  currentFrame  = frameNum_;
  
  return returnVar_;
}

