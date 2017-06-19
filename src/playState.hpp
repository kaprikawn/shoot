#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

//#include <vector>
//#include <map>
#include "SDL.h"
#include "gameState.hpp"
#include "hero.hpp"
#include "target.hpp"
#include "sprite.hpp"
#include "structs.hpp"

class PlayState : public GameState {
  private:
    static const std::string  s_playID;
    
    Hero*       hero_;
    Target*     target_;
    ObjectData  bombObjectData_;
    
    int projectileType_ = 0;
    
  public:
    
    virtual bool onEnter();
    virtual void update( float dt, Uint32 msFrameDiff );
    virtual void render();
    virtual bool onExit();
    
    void  add( Sprite* sprite );
    void  spawnProjectile( int projectileType, Sprite* originSprite );
    
    virtual std::string getStateID() const { return s_playID; }
    
};



#endif //PLAYSTATE_HPP
