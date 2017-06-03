#include <iostream>
#include <vector>
#include "playState.hpp"
#include "jsonLoader.hpp"
#include "structs.hpp"

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
    }
    
    
  }
  
  return true;
}

void PlayState::update( float dt, Uint32 msFrameDiff ) {
  
}

void PlayState::render() {
  for( int i = 0; i < spritesSize_; i++ ) {
    sprites_[i] -> render();
  }
}

bool PlayState::onExit() {
  
  
  std::cout << "exiting PlayState" << std::endl;
  return true;
}
