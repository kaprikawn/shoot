#ifndef TRANSITIONSTATE_HPP
#define TRANSITIONSTATE_HPP

#include <string>
#include "gameState.hpp"
#include "structs.hpp"

class TransitionState : public GameState {
  private:
    static const std::string  s_transitionID;
    
    int transitionType_ = LOADLEVEL;
    int frameNum_ = 20;
    
    std::string levelText_;
    
  public:
    
    virtual bool onEnter();
    virtual void update( float dt, Uint32 msFrameDiff );
    virtual void render();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_transitionID; }
    
};



#endif //TRANSITIONSTATE_HPP
