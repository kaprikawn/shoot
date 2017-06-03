#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "movement.hpp"
#include "animation.hpp"
#include "health.hpp"

class Sprite {
  protected:
  
    ObjectData* objectData_;
    
    DrawFrameParams renderParams_;
    
    Movement    movement_; // position / velocity etc
    Animation   animation_;
    Health      health_;
    
    int         spriteID_;
    
  public:
    Sprite( ObjectData* objectData );
    virtual ~Sprite(){}
    
    virtual void update ( float dt, Uint32 msFrameDiff );
    virtual void render ();
    virtual void clean  ();
    
    
};

#endif //SPRITE_HPP
