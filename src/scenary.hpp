#ifndef SCENARY_HPP
#define SCENARY_HPP

#include "sprite.hpp"

class Scenary : public Sprite {
  
  private:
    
  public:
    
    Scenary( std::unique_ptr<ObjectData> objectData );
    virtual ~Scenary(){}
    
    virtual void update ( float dt, Uint32 msFrameDiff );
    virtual void render ();
    virtual void clean  ();
    
    
};

#endif //SCENARY_HPP
