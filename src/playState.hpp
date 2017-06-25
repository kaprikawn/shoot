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
#include "collision.hpp"
#include "hud.hpp"

class PlayState : public GameState {
  private:
    static const std::string  s_playID;
    
    std::vector<std::unique_ptr<ObjectData>> commonObjectsData_; // hero, target etc.
    std::vector<std::unique_ptr<ObjectData>> levelObjectsData_; // enemies, scenary etc.
    
    Hero*       hero_;
    Target*     target_;
    Hud*        hud_;
    
    ObjectData  pBombObjectData_;
    
    std::string backgroundFilename_;
    int         pointsNeeded_;
    
    Sprite*     spriteHit_ = nullptr; // which sprite got hit by player shot
    Collision   myCollision_;
    std::vector<std::pair<Sprite*, Sprite*>> collisions_;
    
    int spriteOnePos_;
    int spriteTwoPos_;
    
    //std::vector<ObjectData*> enemies_;
    std::map<int, int> src; // map of draw indexes so we know which order to draw
    std::multimap<int, int> dst;
    
    int     projectileType_ = 0;
    int     nextSpriteID_   = 0;
    int     newSpriteID_    = 0;
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
    
    bool  loadLevelFromFile( int currentLevel );
    int   getSpriteVectorPosition( int spriteID );
    
};



#endif //PLAYSTATE_HPP
