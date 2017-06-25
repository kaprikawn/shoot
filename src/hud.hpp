#ifndef HUD_HPP
#define HUD_HPP

#include <memory>
#include "structs.hpp"
#include "SDL.h"
#include "SDL_ttf.h"

class Hud {
  
  private:
    
    int points_;
    int pointsNeeded_;
    
    int yellowWidth_, redWidth_;
    
    SDL_Renderer* renderer_;
    SDL_Rect rect_;
    
    TTF_Font* font_;
    
  public:
    
    Hud( int pointsNeeded );
    virtual ~Hud(){}
    
    void update ( float dt, Uint32 msFrameDiff );
    void render ();
    void clean  ();
    
};

#endif //HUD_HPP
