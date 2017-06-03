#include <iostream>
#include <vector>
#include "playState.hpp"
#include "jsonLoader.hpp"
#include "structs.hpp"

const std::string PlayState::s_playID = "PLAY";

bool PlayState::onEnter() {
  JsonLoader jsonLoader;
  std::vector<ObjectData*> objectData = jsonLoader.getObjectData( "assets/dataMain.json" );
  
  for( unsigned int i = 0; i < objectData.size(); i++ ) {
    if( objectData[i] -> objectType == "Player" ) {
      printf( "found player\n" );
    }
  }
  
  return true;
}

void PlayState::update( float dt, Uint32 msFrameDiff ) {
  
}

void PlayState::render() {

}

bool PlayState::onExit() {
  
  
  std::cout << "exiting PlayState" << std::endl;
  return true;
}
