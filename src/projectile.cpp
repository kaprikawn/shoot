#include <iostream>
#include "projectile.hpp"

Projectile::Projectile( ObjectData* objectData, ProjectileData &projectileData ) : Sprite( objectData ) {
  velocity_ = Vector( Vector( projectileData.dstX, projectileData.dstY ) - Vector( projectileData.srcX, projectileData.srcY ) );
  
}

void Projectile::update( float dt, Uint32 msFrameDiff ) {
  Sprite::update( dt, msFrameDiff );
}

void Projectile::render() {
  Sprite::render();
}

void Projectile::clean() {

}
