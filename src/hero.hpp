#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "sprite.hpp"


class Hero : public Sprite {
  
  private:
  
    int     lastDirection_  = 0;
    Uint32  bulletCooldown_ = 0;
    Uint32  bombCooldown_   = 0;
    
  public:
    
    Hero( ObjectData* objectData );
    virtual ~Hero(){}
    
    virtual void update ( float dt, Uint32 msFrameDiff );
    virtual void render ();
    virtual void clean  ();
    
    void handleInput();
    
};

#endif //PLAYER_HPP
