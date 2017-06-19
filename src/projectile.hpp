#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "sprite.hpp"
#include "structs.hpp"
#include "vector.hpp"

class Projectile : public Sprite {
  
  private:
  
    int projectileType_ = 0;
    
    int   srcX;
    int   srcY;
    int   dstX;
    int   dstY;
    bool  destroyAtDest_;
    bool  testOnY = true; // whether to test whether passed position on X or Y
    
  public:
    
    //Projectile( int x, int y, int destinationX, int destinationY, int speed, bool deleteAtDestination, bool isHostile, bool isPlayerGenerated );
    Projectile( ObjectData* objectData, ProjectileData &projectileData );
    virtual ~Projectile(){}
    
    virtual void update ( float dt, Uint32 msFrameDiff );
    virtual void render ();
    virtual void clean  ();
    
    bool hasPassedDestination();
    
    
};

#endif //PROJECTILE_HPP

