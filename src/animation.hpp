#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <unordered_map>
#include <vector>
#include "SDL.h"
#include "structs.hpp"

class Animation {
  
  private:
    //std::vector<StateData*>       stateData_;
    //std::vector<AnimationData*>   animationData_;
    
    //bool    fixedAnimation_       = false;
    
    int currentFrame_ = 0;
    int currentRow_ = 1;
    
    Uint32 frameDuration_ = 100;
    Uint32 msSinceLastChange_ = 0;
    bool changeFrame_ = false;
    
    
  public:
    Animation();
    ~Animation(){}
    
    bool determineFrame( int spriteState, float dt, Uint32 mfFrameDiff
      , int& currentFrame
      , int& currentRow
      , float& scale
    );
    
    
    
};

#endif //ANIMATION_HPP
