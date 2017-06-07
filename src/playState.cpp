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
    }
  }
  
  TheTextures::Instance() -> load( "assets/level1Background.png", "background" );
  TheTextures::Instance() -> load( "assets/bomb.png", "bomb" );
  
  return true;
}

void PlayState::spawnProjectile( int projectileType, Sprite* originSprite ) {
  ObjectData* newObjectData = new ObjectData();
  
  //projectileData -> spriteID
  newObjectData -> width      = 30;
  newObjectData -> height     = 30;
  newObjectData -> x          = hero_ -> getMovement().getSpriteCenter().getX();
  newObjectData -> y          = hero_ -> getMovement().getSpriteCenter().getY();
  newObjectData -> objectType = "projectile";
  newObjectData -> textureID  = "bomb";
  newObjectData -> name       = "proj";
  newObjectData -> filename   = "assets/bomb.png";
  
  StateData newStateData;
  newStateData.id = "DEFAULT";
  newStateData.spriteState = 0;
  
  AnimationData newAnimationData;
  newStateData.animData.push_back( newAnimationData );
  
  newObjectData -> stateData.push_back( newStateData );
  
  ProjectileData projectileData;
  
  projectileData.type = projectileType;
  projectileData.srcX = newObjectData -> x;
  projectileData.srcY = newObjectData -> y;
  projectileData.dstX = target_ -> getMovement().getSpriteCenter().getX();
  projectileData.dstY = target_ -> getMovement().getSpriteCenter().getY();
  
  if( projectileType == PBULLET ) {
    projectileData.speedFactor = 7.0f;
  } else if( projectileType == PBOMB ) {
    projectileData.speedFactor = 1.8f;
  }
  
  Projectile* newProjectile = new Projectile( newObjectData, projectileData );
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
