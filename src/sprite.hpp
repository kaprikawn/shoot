#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <memory>
#include "position.hpp"
#include "animation.hpp"
#include "health.hpp"
#include "vector.hpp"

class Sprite {
  protected:
  
    std::unique_ptr<ObjectData> objectData_;
    
    DrawFrameParams renderParams_;
    
    Health      health_;
    Position    position_; // position / velocity etc
    Vector      velocity_;
    Animation   animation_; // animation handler
    
    float       elevation_;
    Vector      elevationP_; // elevation postition
    Vector      elevationV_; // elevation vector
    Vector      elevationG_; // elevation gravity
    
    int         spriteID_;
    int         spriteState_      = 0;
    int         prevSpriteState_  = 0;
    
    bool        ignoreScale_      = false;
    bool        fixedAnimDone_; // used only for fixed animations
    
    int         spawnProjectile_  = 0; // number refers to type of projectile
    int         drawIndex_; // for use in deciding which order to draw sprites in
    int         zIndex_ = 0; // y coordinate of the bottom of the sprite
    bool        deleteSprite_     = false;
    
    bool        testOnY_    = true; // whether to test whether passed position on X or Y
    bool        showHitbox_ = true;
    
    bool        hostileToHero_ = false; // whether this is something that hurts player
    bool        hostileToEnemy_ = false; // whether this is something that hurts enemy
    
  public:
    Sprite( std::unique_ptr<ObjectData> objectData );
    virtual ~Sprite(){}
    
    virtual void update ( float dt, Uint32 msFrameDiff );
    virtual void render ();
    virtual void clean  ();
    
    int spawnProjectile() {
      return spawnProjectile_;
    }
    
    void setSpawnProjectile( bool spawnProjectile ) {
      spawnProjectile_ = spawnProjectile;
    }
    
    bool  needsDeleting()   { return deleteSprite_; }
    int   getDrawIndex()    { return drawIndex_; }
    int   getSpriteID()     { return objectData_ -> spriteID; }
    int   getSpriteState()  { return spriteState_; }
    int   getZIndex()       { return zIndex_; }
    
    bool  isHostileToHero()   { return hostileToHero_; }
    bool  isHostileToEnemy()  { return hostileToEnemy_; }
    
    std::string getObjectType() { return objectData_ -> objectType; }
    
    bool  hasPassedDestination( int srcX, int srcY, int dstX, int dstY );
    
    void  setSpriteID( int spriteID ) { objectData_ -> spriteID = spriteID; }
    
    void  reduceHp( int attackAmount );
    
    
    
    Position getPosition() { return position_; }
    
};

#endif //SPRITE_HPP
