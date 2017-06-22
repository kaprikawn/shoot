#include <iostream>
#include "projectile.hpp"

Projectile::Projectile( ObjectData* objectData, ProjectileData &projectileData ) : Sprite( objectData ) {
  
  projectileData_ = projectileData;
  
  velocity_ = Vector( Vector( projectileData.dstX, projectileData.dstY ) - Vector( projectileData.srcX, projectileData.srcY ) );
  
  std::cout << "vx is " << velocity_.getX() << std::endl;
  std::cout << "vy is " << velocity_.getY() << std::endl;
  
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
  
  /*if( elevationP_.getY() > 0 ) {
    velocity_.setX( 0 );
    velocity_.setY( 0 );
    spriteState_ = DYING;
  }*/

  Sprite::update( dt, msFrameDiff );
  drawIndex_ += 1000;
  
  /*if( projectileData_.destroyAtDest && hasPassedDestination() ) {
    deleteSprite_ = true;
  }*/
  
  if( Projectile::hasPassedDestination() ) {
    if( projectileData_.type == PBOMB ) {
      velocity_.setX( 0 );
      velocity_.setY( 0 );
      spriteState_ = DYING;
    } else if( projectileData_.destroyAtDest ) {
      deleteSprite_ = true;
    }
  }
  
  if( fixedAnimDone_ ) {
    deleteSprite_ = true;
  }
  
  std::cout << "x is " << position_.getCoordinates().getX() << std::endl;
  std::cout << "y is " << position_.getCoordinates().getY() << std::endl;
  
  
  //std::cout << "elevation is " << elevationP_.getY() << std::endl;
}

void Projectile::render() {
  Sprite::render();
}

void Projectile::clean() {
  
}
