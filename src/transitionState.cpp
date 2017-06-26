#include <iostream>
#include <sstream>
#include "transitionState.hpp"
#include "values.hpp"
#include "textures.hpp"
#include "game.hpp"

const std::string TransitionState::s_transitionID = "TRANSITION";

bool TransitionState::onEnter() {
  
  std::stringstream ss;
  ss << "Level " << TheValues::Instance() -> getCurrentLevelStr();
  levelText_ = ss.str();
  
  //std::cout << "current level is " << currentLevel_ << std::endl;
  if( !TheTextures::Instance() -> loadFont( 40 ) ) {
    std::cout << "Failed to load font\n" << std::endl;
    return false;
  }
  
  return true;
}

void TransitionState::update( float dt, Uint32 msFrameDiff ) {
  frameNum_ --;
  
  if( frameNum_ <= 0 ) {
    TheGame::Instance() -> changeGameState( PLAY );
  }
}


void TransitionState::render() {
  //printf( "rendering transition state\n" );
  
  if( transitionType_ == LOADLEVEL ) {
    TheTextures::Instance() -> drawFont( levelText_, 40, "white", 10, 10, 100, 100, true );
  }
  
}

bool TransitionState::onExit() {

  return true;
}
