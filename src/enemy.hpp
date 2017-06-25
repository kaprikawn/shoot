#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <vector>
#include "sprite.hpp"
#include "vector.hpp"
#include "structs.hpp"

class Enemy : public Sprite {
  private:
    int       pathDataIndex_ = 0;
    bool      recalculateVelocity_ = true;
    Vector    destination_;
    
    std::vector<Path> paths_;
    int   srcX_, srcY_, dstX_, dstY_;
    
    int yellowWidth_, redWidth_; // for lifebar
  
  public:
    
    Enemy( std::unique_ptr<ObjectData> objectData );
    virtual ~Enemy(){}
    
    virtual void update ( float dt, Uint32 msFrameDiff );
    virtual void render ();
    virtual void clean  ();
    
    void calculateVelocity( int pathDataIndex );
    void renderLifebar();
};

#endif //ENEMY_HPP
