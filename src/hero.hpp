#ifndef HERO_HPP
#define HERO_HPP

#include <memory>
#include "sprite.hpp"

class Hero : public Sprite {
  
  private:
  
    int     lastDirection_  = 0;
    Uint32  bulletCooldown_ = 0;
    Uint32  bombCooldown_   = 0;
    Uint32  invCounter_     = 0;
    
    int     startupDelay_   = 10;
    
  public:
    
    Hero( std::unique_ptr<ObjectData> objectData );
    virtual ~Hero(){}
    
    virtual void update ( float dt, Uint32 msFrameDiff );
    virtual void render ();
    virtual void clean  ();
    
    void handleInput();
    
    bool isInv() { // is invulnerable
      if( invCounter_ > 0 ) {
        return true;
      } else {
        return false;
      }
    }
    
};

#endif //HERO_HPP
