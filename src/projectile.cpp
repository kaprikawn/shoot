#include <iostream>
#include "projectile.hpp"

Projectile::Projectile( std::unique_ptr<ObjectData> objectData, ProjectileData &projectileData ) : Sprite( std::move( objectData ) ) {
  
  projectileData_ = projectileData;
  
  velocity_ = Vector( Vector( projectileData.dstX, projectileData.dstY ) - Vector( projectileData.srcX, projectileData.srcY ) );
  
  velocity_ *= projectileData.speedFactor;
  
  if( projectileData.type == PROJECTILEHEROBOMB || projectileData.type == PROJECTILEENEMYCHUCKER ) {
    
    int y = -1000 * projectileData.speedFactor;
    int g = sqrt( y * y ) * projectileData.speedFactor;
    g *= 2;
      
    elevationV_.setY( y );
    elevationG_.setY( g );
    
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
  
  //std::cout << "size of animation data is " << ( *objectData_ ).stateData.size() << std::endl;
  
  //std::cout << "textureID is " << ( *objectData_ ).textureID << std::endl;
  
  Sprite::update( dt, msFrameDiff );
  
  if( Projectile::hasPassedDestination() ) {
    if( projectileData_.type == PROJECTILEHEROBOMB || projectileData_.type == PROJECTILEENEMYCHUCKER ) {
      velocity_.setX( 0 );
      velocity_.setY( 0 );
      spriteState_ = DYING;
      drawIndex_ += 10000; // make sure it appears in front
      if( projectileData_.type == PROJECTILEHEROBOMB ) {
        hostileToEnemy_ = true;
      } else if( projectileData_.type == PROJECTILEENEMYCHUCKER ) {
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
