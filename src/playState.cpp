#include <iostream>
#include <vector>
#include "playState.hpp"
#include "jsonLoader.hpp"
#include "structs.hpp"
#include "textures.hpp"

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
  
  return true;
}

void PlayState::update( float dt, Uint32 msFrameDiff ) {
  for( int i = 0; i < spritesSize_; i++ ) {
    sprites_[i] -> update( dt, msFrameDiff );
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
