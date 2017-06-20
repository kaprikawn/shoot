#include <iostream>
#include "projectile.hpp"

Projectile::Projectile( ObjectData* objectData, ProjectileData &projectileData ) : Sprite( objectData ) {
  
  projectileData_ = projectileData;
  
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
    
    projectileData_.canDamage = false;
  }
  
  if( projectileData_.destroyAtDest ) {
    // if the projectile is going more horizontally than vertically
    // test whether it has passed the target based on X coordinates, otherwise default Y
    if( abs( projectileData_.dstY - projectileData_.srcY ) < abs( projectileData_.dstX - projectileData_.srcX ) ) {
      testOnY = false;
    }
  }
  
}

bool Projectile::hasPassedDestination() {
  
  if( testOnY ) {
    if( projectileData_.dstY <= projectileData_.srcY && movement_.getCoordinates().getY() <= projectileData_.dstY ) {
      return true;
    } else if( projectileData_.dstY >= projectileData_.srcY && movement_.getCoordinates().getY() >= projectileData_.dstY ) {
      return true;
    }
  } else {
    if( projectileData_.dstX >= projectileData_.srcX && movement_.getCoordinates().getX() >= projectileData_.dstX ) {
      return true;
    } else if( projectileData_.dstX <= projectileData_.srcX && movement_.getCoordinates().getX() <= projectileData_.dstX ) {
      return true;
    }
  }
  return false;
}

void Projectile::update( float dt, Uint32 msFrameDiff ) {
  
  if( elevationP_.getY() > 0 ) {
    velocity_.setX( 0 );
    velocity_.setY( 0 );
    spriteState_ = DYING;
  }

  Sprite::update( dt, msFrameDiff );
  
  if( projectileData_.destroyAtDest && hasPassedDestination() ) {
    deleteSprite_ = true;
  }
  
  if( fixedAnimDone_ ) {
    deleteSprite_ = true;
  }
  
  
  //std::cout << "elevation is " << elevationP_.getY() << std::endl;
}

void Projectile::render() {
  Sprite::render();
}

void Projectile::clean() {
  printf( "calling clean\n" );
}
