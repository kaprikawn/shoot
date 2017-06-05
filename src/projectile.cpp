#include <iostream>
#include "projectile.hpp"

Projectile::Projectile( ObjectData* objectData, ProjectileData &projectileData ) : Sprite( objectData ) {
  velocity_ = Vector( Vector( projectileData.dstX, projectileData.dstY ) - Vector( projectileData.srcX, projectileData.srcY ) );
  
  //velocity_ *= 2;
  
  int y = -1000;
  int g = sqrt( y * y );
  g *= 2;
  
  //printf( "y is %d\n", y );
  //printf( "g is %d\n", g );
    
  elevationV_.setY( -1000 );
  elevationG_.setY( sqrt( elevationV_.getY() * elevationV_.getY() ) * 2 );
}

void Projectile::update( float dt, Uint32 msFrameDiff ) {
  Sprite::update( dt, msFrameDiff );
  
  //std::cout << "elevation is " << elevationP_.getY() << std::endl;
}

void Projectile::render() {
  Sprite::render();
}

void Projectile::clean() {

}
