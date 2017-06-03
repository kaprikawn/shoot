#ifndef GAMESTATEMACHINE_HPP
#define GAMESTATEMACHINE_HPP

#include <vector>
#include "gameState.hpp"

class GameStateMachine {
  private:
    std::vector<GameState*> gameStates_;
    
  public:
    void pushState  ( GameState* state );
    void changeState( GameState* state );
    void popState   ();
    
    void update     ( float dt, Uint32 msFrameDiff );
    void render     ();
    
    std::string     getCurrentGameStateID();
};

#endif //GAMESTATEMACHINE_HPP
