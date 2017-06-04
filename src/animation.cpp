#include <iostream>
#include "animation.hpp"
#include "structs.hpp"

Animation::Animation( std::vector<StateData>& stateData ) {
  stateData_ = stateData; // copy the state data from the objectData loaded in by json
}

void Animation::changeState( int newSpriteState ) {
  animationData_.clear();
  
  for( unsigned int i = 0; i < stateData_.size(); i++ ) {
    if( stateData_[i].spriteState == newSpriteState ) {
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
    , float& scale
  ) {
  
  msSinceLastChange_ += mfFrameDiff;
  frameNum_ = currentFrame;
  
  changeFrame_ = false;
  if( animationData_.empty() || spriteState != lastSpriteState_ ) {
    Animation::changeState( spriteState );
  }
  
  if( msSinceLastChange_ > animationData_[ currentIndex_ ].duration ) {
    changeFrame_ = true;
    msSinceLastChange_ = 0;
  }
  
  if( changeFrame_ ) {
    frameNum_ += frameStep_;
  }
  
  if( frameNum_ > animationData_[ currentIndex_ ].maxFrame ) {
    frameNum_ = animationData_[ currentIndex_ ].minFrame;
  }
  
  if( frameNum_ < animationData_[ currentIndex_ ].minFrame || frameNum_ < 0 ) {
    frameNum_ = animationData_[ currentIndex_ ].minFrame;
  }
  
  currentFrame = frameNum_;
  currentRow = 1;
  scale = 1.0f;
  
  return false;
}

