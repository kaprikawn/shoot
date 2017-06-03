#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <unordered_map>
#include <vector>
#include "SDL.h"
#include "structs.hpp"

class Animation {
  
  private:
    std::vector<StateData*>       stateData_;
    std::vector<AnimationData*>   animationData_;
    
    bool    fixedAnimation_       = false;
    
    
  public:
    Animation(){}
    ~Animation(){}
    
    
};

#endif //ANIMATION_HPP
