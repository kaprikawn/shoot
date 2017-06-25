#ifndef TARGET_HPP
#define TARGET_HPP

#include "sprite.hpp"

class Target : public Sprite {
  
  private:
    
    void  handleInput();
    int   startupDelay_ = 10;
    
    
  public:
    
    Target( std::unique_ptr<ObjectData> objectData );
    virtual ~Target(){}
    
    virtual void update ( float dt, Uint32 msFrameDiff );
    virtual void render ();
    virtual void clean  ();
    
    
};

#endif //TARGET_HPP
