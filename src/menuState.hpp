#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include <string>
#include "gameState.hpp"
#include "structs.hpp"

class MenuState : public GameState {
  private:
    static const std::string  s_menuID;
    
    std::string displayText_;
    
    DrawFrameParams playRenderParams_;
    DrawFrameParams quitRenderParams_;
    
    bool playSelected_ = true;
    
  public:
    
    virtual bool onEnter();
    virtual void update( float dt, Uint32 msFrameDiff );
    virtual void render();
    virtual bool onExit();
    
    void handleInput();
    
    virtual std::string getStateID() const { return s_menuID; }
    
};



#endif //MENUSTATE_HPP
