#include <iostream>
#include "projectile.hpp"

Projectile::Projectile( ObjectData* objectData, ProjectileData &projectileData ) : Sprite( objectData ) {
  velocity_ = Vector( Vector( projectileData.dstX, projectileData.dstY ) - Vector( projectileData.srcX, projectileData.srcY ) );
  
  //float speedFactor = 1.8f;
  
  velocity_ *= projectileData.speedFactor;
  
  if( projectileData.type == PBOMB ) {
  
    int y = -1000 * projectileData.speedFactor;
    int g = sqrt( y * y ) * projectileData.speedFactor;
    g *= 2;
    
    //printf( "y is %d\n", y );
    //printf( "g is %d\n", g );
      
    elevationV_.setY( y );
    elevationG_.setY( g );
  }
  
}

void Projectile::update( float dt, Uint32 msFrameDiff ) {
  
  if( elevationP_.getY() > 0 ) {
    velocity_.setX( 0 );
    velocity_.setY( 0 );
  }

  Sprite::update( dt, msFrameDiff );
  
  //std::cout << "elevation is " << elevationP_.getY() << std::endl;
}

void Projectile::render() {
  Sprite::render();
}

void Projectile::clean() {

}
