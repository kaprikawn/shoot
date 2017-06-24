#include <iostream>
#include "projectile.hpp"

Projectile::Projectile( ObjectData* objectData, ProjectileData &projectileData ) : Sprite( objectData ) {
  
  projectileData_ = projectileData;
  
  velocity_ = Vector( Vector( projectileData.dstX, projectileData.dstY ) - Vector( projectileData.srcX, projectileData.srcY ) );
  
  velocity_ *= projectileData.speedFactor;
  
  if( projectileData.type == PBOMB || projectileData.type == EBOMB ) {
  
    int y = -1000 * projectileData.speedFactor;
    int g = sqrt( y * y ) * projectileData.speedFactor;
    g *= 2;
      
    elevationV_.setY( y );
    elevationG_.setY( g );
    
    projectileData_.canDamage = false;
    
  }
  
  if( projectileData.type == PBULLET ) {
    objectData -> objectType = "PBullet";
  }
  
  // if the projectile is going more horizontally than vertically
  // test whether it has passed the target based on X coordinates, otherwise default Y
  if( abs( projectileData_.dstY - projectileData_.srcY ) < abs( projectileData_.dstX - projectileData_.srcX ) ) {
    testOnY_ = false;
  }
  
}

bool Projectile::hasPassedDestination() {
  
  if( testOnY_ ) {
    if( projectileData_.dstY <= projectileData_.srcY && position_.getCoordinates().getY() <= projectileData_.dstY ) {
      return true;
    } else if( projectileData_.dstY >= projectileData_.srcY && position_.getCoordinates().getY() >= projectileData_.dstY ) {
      return true;
    }
  } else {
    if( projectileData_.dstX >= projectileData_.srcX && position_.getCoordinates().getX() >= projectileData_.dstX ) {
      return true;
    } else if( projectileData_.dstX <= projectileData_.srcX && position_.getCoordinates().getX() <= projectileData_.dstX ) {
      return true;
    }
  }
  return false;
}

void Projectile::update( float dt, Uint32 msFrameDiff ) {

  Sprite::update( dt, msFrameDiff );
  
  if( Projectile::hasPassedDestination() ) {
    if( projectileData_.type == PBOMB || projectileData_.type == EBOMB ) {
      velocity_.setX( 0 );
      velocity_.setY( 0 );
      spriteState_ = DYING;
      drawIndex_ += 10000; // make sure it appears in front
      if( projectileData_.type == PBOMB ) {
        hostileToEnemy_ = true;
      } else if( projectileData_.type == EBOMB ) {
        hostileToHero_ = true;
      }
      
    } else if( projectileData_.destroyAtDest ) {
      deleteSprite_ = true;
    }
  }
  
  if( fixedAnimDone_ ) {
    deleteSprite_ = true;
  }
}

void Projectile::render() {
  Sprite::render();
}

void Projectile::clean() {
  Sprite::clean();
}
