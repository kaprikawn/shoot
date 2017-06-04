#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <unordered_map>
#include <vector>
#include "SDL.h"
#include "structs.hpp"

class Animation {
  
  private:
    std::vector<StateData>      stateData_;
    std::vector<AnimationData>  animationData_;
    unsigned int                currentIndex_ = 0; // index of current frame of animation in animationData_
    
    int currentFrame_     = 0;
    int currentRow_       = 1;
    int lastSpriteState_  = 0;
    
    Uint32  frameDuration_      = 100;
    Uint32  msSinceLastChange_  = 0;
    bool    changeFrame_        = false;
    
    int     frameStep_          = 1; // whether to go up or down
    int     frameNum_           = 0;
    bool    returnVar_          = false;
    bool    fixedAnim_          = false;
    
    
  public:
    Animation( std::vector<StateData>& stateData );
    ~Animation(){}
    
    bool determineFrame( int spriteState, float dt, Uint32 mfFrameDiff
      , int& currentFrame
      , int& currentRow
      , float& scale
    );
    
    void changeState( int newSpriteState );
    
    
    
};

#endif //ANIMATION_HPP
