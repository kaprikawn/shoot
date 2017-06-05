#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "sprite.hpp"
#include "structs.hpp"
#include "vector.hpp"

class Projectile : public Sprite {
  
  private:
    int projectileType_ = 0;
    
    
  public:
    
    //Projectile( int x, int y, int destinationX, int destinationY, int speed, bool deleteAtDestination, bool isHostile, bool isPlayerGenerated );
    Projectile( ObjectData* objectData, ProjectileData &projectileData );
    virtual ~Projectile(){}
    
    virtual void update ( float dt, Uint32 msFrameDiff );
    virtual void render ();
    virtual void clean  ();
    
    
};

#endif //PROJECTILE_HPP

