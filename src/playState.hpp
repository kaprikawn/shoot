#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

//#include <vector>
#include <map>
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
    ObjectData  pBombObjectData_;
    ObjectData  eBombObjectData_;
    
    std::vector<ObjectData*> enemies_;
    std::map<int, int> src; // map of draw indexes so we know which order to draw
    std::multimap<int, int> dst;
    
    int     projectileType_ = 0;
    Uint32  levelStart_;
    Uint32  currentTime_;
    
  public:
    
    virtual bool onEnter();
    virtual void update( float dt, Uint32 msFrameDiff );
    virtual void render();
    virtual bool onExit();
    
    void  add( Sprite* sprite );
    void  spawnProjectile( int projectileType, Sprite* originSprite );
    
    virtual std::string getStateID() const { return s_playID; }
    
    bool loadLevelFromFile( int currentLevel );
    
};



#endif //PLAYSTATE_HPP
