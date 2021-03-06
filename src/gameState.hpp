#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <string>
#include <memory>
#include "SDL.h"
#include "sprite.hpp"

class GameState {
  protected:
    GameState() {}
    
    std::vector <Sprite*> sprites_;
    
    //std::vector<std::unique_ptr<Sprite>> sprites_;
    
    int spritesSize_   = 0;
    //int nextSpriteID  = 0;
    
  public:
    virtual ~GameState() {}
    
    virtual bool onEnter() = 0;
    virtual void update ( float dt, Uint32 msFrameDiff ) = 0;
    virtual void render () = 0;
    virtual bool onExit () = 0;
    virtual std::string getStateID() const = 0;
};

#endif //GAMESTATE_HPP
