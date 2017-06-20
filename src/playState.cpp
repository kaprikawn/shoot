#include <iostream>
#include <vector>
#include "playState.hpp"
#include "jsonLoader.hpp"
#include "structs.hpp"
#include "textures.hpp"
#include "projectile.hpp"

const std::string PlayState::s_playID = "PLAY";

void PlayState::add( Sprite* sprite ) {
  sprites_.push_back( sprite );
  spritesSize_ = sprites_.size();
}

bool PlayState::onEnter() {
  JsonLoader jsonLoader;
  std::vector<ObjectData*> objectData = jsonLoader.getObjectData( "assets/dataMain.json" );
  
  for( unsigned int i = 0; i < objectData.size(); i++ ) {
    if( objectData[i] -> objectType == "Hero" ) {
      hero_ = new Hero( objectData[i] );
      PlayState::add( hero_ );
    } else if( objectData[i] -> objectType == "Target" ) {
      target_ = new Target( objectData[i] );
      PlayState::add( target_ );
    } else if( objectData[i] -> objectType == "Bomb" ) {
      bombObjectData_ = ( *objectData[i] );
    }
  }
  
  TheTextures::Instance() -> load( "assets/level1Background.png", "background" );
  TheTextures::Instance() -> load( "assets/bomb.png", "bomb" );
  
  return true;
}

void PlayState::spawnProjectile( int projectileType, Sprite* originSprite ) {
  
  bombObjectData_.x = hero_ -> getMovement().getSpriteCenter().getX();
  bombObjectData_.y = hero_ -> getMovement().getSpriteCenter().getY();
  
  ProjectileData projectileData;
  
  projectileData.type = projectileType;
  projectileData.srcX = bombObjectData_.x;
  projectileData.srcY = bombObjectData_.y;
  projectileData.dstX = target_ -> getMovement().getSpriteCenter().getX();
  projectileData.dstY = target_ -> getMovement().getSpriteCenter().getY();
  
  if( projectileType == PBULLET ) {
    projectileData.speedFactor = 7.0f;
    projectileData.destroyAtDest = true;
  } else if( projectileType == PBOMB ) {
    projectileData.speedFactor = 1.8f;
  }
  
  Projectile* newProjectile = new Projectile( &bombObjectData_, projectileData );
  PlayState::add( newProjectile );
}

void PlayState::update( float dt, Uint32 msFrameDiff ) {
  for( int i = 0; i < spritesSize_; i++ ) {
    sprites_[i] -> update( dt, msFrameDiff );
    
    projectileType_ = sprites_[i] -> spawnProjectile();
    if( projectileType_ > 0 ) {
      PlayState::spawnProjectile( projectileType_, sprites_[i]  );
    }
  }
  
  //delete dead stuff
  for( unsigned i = spritesSize_; i-- > 0; ) {
    if( sprites_[i] -> needsDeleting() ) {
      //printf( "deleting %d\n", i );
      delete sprites_[i];
      sprites_.erase( sprites_.begin() + i );
    }
  }
  spritesSize_ = sprites_.size();
}

void PlayState::render() {
  
  TheTextures::Instance() -> draw( "background", 0, 0, 1280, 720 );
  
  for( int i = 0; i < spritesSize_; i++ ) {
    sprites_[i] -> render();
  }
}

bool PlayState::onExit() {
  
  
  std::cout << "exiting PlayState" << std::endl;
  return true;
}
