#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "sprite.hpp"
#include "structs.hpp"
#include "vector.hpp"

class Projectile : public Sprite {
  
  private:
    ProjectileData projectileData_;
    
    int projectileType_ = 0;
    
  public:
    
    Projectile( std::unique_ptr<ObjectData> objectData, ProjectileData &projectileData );
    virtual ~Projectile(){}
    
    virtual void update ( float dt, Uint32 msFrameDiff );
    virtual void render ();
    virtual void clean  ();
    
    bool hasPassedDestination();
    
    
};

#endif //PROJECTILE_HPP

