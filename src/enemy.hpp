#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <vector>
#include "sprite.hpp"

class Enemy : public Sprite {
  private:
  
  public:
    
    Enemy( ObjectData* objectData );
    virtual ~Enemy(){}
    
    virtual void update ( float dt, Uint32 msFrameDiff );
    virtual void render ();
    virtual void clean  ();
};

#endif //ENEMY_HPP
