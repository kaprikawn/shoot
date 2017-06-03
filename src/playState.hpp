#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

//#include <vector>
//#include <map>
#include "SDL.h"
#include "gameState.hpp"

class PlayState : public GameState {
  private:
    static const std::string  s_playID;
    
  public:
    
    virtual bool onEnter();
    virtual void update( float dt, Uint32 msFrameDiff );
    virtual void render();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_playID; }
    
};



#endif //PLAYSTATE_HPP
