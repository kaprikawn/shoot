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
    
    
    Animation   animation_;
    Health      health_;
    Movement    movement_; // position / velocity etc
    Vector      velocity_;
    
    int         spriteID_;
    int         spriteState_ = 0;
    
  public:
    Sprite( ObjectData* objectData );
    virtual ~Sprite(){}
    
    virtual void update ( float dt, Uint32 msFrameDiff );
    virtual void render ();
    virtual void clean  ();
    
    
};

#endif //SPRITE_HPP
