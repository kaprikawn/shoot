#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "movement.hpp"
#include "animation.hpp"
#include "health.hpp"
#include "vector.hpp"

class Sprite {
  protected:
  
    ObjectData* objectData_;
    
    DrawFrameParams renderParams_;
    
    Health      health_;
    Movement    movement_; // position / velocity etc
    Vector      velocity_;
    Animation   animation_; // animation handler
    
    Vector      elevationP_; // elevation postition
    Vector      elevationV_; // elevation vector
    Vector      elevationG_; // elevation gravity
    
    int         spriteID_;
    int         spriteState_      = 0;
    
    bool        ignoreScale_      = false;
    bool        fixedAnimDone_; // used only for fixed animations
    
    int         spawnProjectile_  = 0; // number refers to type of projectile
    
    bool        deleteSprite_     = false;
    
  public:
    Sprite( ObjectData* objectData );
    virtual ~Sprite(){}
    
    virtual void update ( float dt, Uint32 msFrameDiff );
    virtual void render ();
    virtual void clean  ();
    
    int spawnProjectile() {
      return spawnProjectile_;
    }
    
    bool needsDeleting() { return deleteSprite_; }
    
    //void setDelete() { deleteSprite_ = true; }
    
    Movement getMovement() { return movement_; }
    
};

#endif //SPRITE_HPP
