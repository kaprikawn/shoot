#include <iostream>
#include "projectile.hpp"

Projectile::Projectile( ObjectData* objectData, ProjectileData &projectileData ) : Sprite( objectData ) {
  velocity_ = Vector( Vector( projectileData.dstX, projectileData.dstY ) - Vector( projectileData.srcX, projectileData.srcY ) );
  
  elevationV_.setY( -200 );
  elevationG_.setY( 100 );
}

void Projectile::update( float dt, Uint32 msFrameDiff ) {
  Sprite::update( dt, msFrameDiff );
  
  
  
  std::cout << "elevation is " << elevationP_.getY() << std::endl;
  
}

void Projectile::render() {
  Sprite::render();
}

void Projectile::clean() {

}
