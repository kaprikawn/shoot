#include <iostream>
#include <sstream>
#include "transitionState.hpp"
#include "values.hpp"
#include "textures.hpp"
#include "game.hpp"

const std::string TransitionState::s_transitionID = "TRANSITION";

bool TransitionState::onEnter() {
  
  std::stringstream ss;
  
  if( transitionType_ == SPLASH ) {
    ss << "kaprikawn games presents..." << TheValues::Instance() -> getCurrentStage();
    frameNum_ = 60;
  } else if( TheValues::Instance() -> getLives() <= 0 ) {
    // game over state
    ss << "Ya done goofed - you reached level " << TheValues::Instance() -> getCurrentStage();
    transitionType_ = GAMEOVER;
  } else {
    ss << "Stage " << TheValues::Instance() -> getNextStage();
  }
  
  displayText_ = ss.str();
  
  //std::cout << "current level is " << currentLevel_ << std::endl;
  if( !TheTextures::Instance() -> loadFont( 40 ) ) {
    std::cout << "Failed to load font\n" << std::endl;
    return false;
  }
  
  return true;
}

void TransitionState::handleInput() {

}

void TransitionState::update( float dt, Uint32 msFrameDiff ) {
  
  if( transitionType_ == LOADLEVEL  ) {
    frameNum_ --;
    
    if( frameNum_ <= 0 ) {
      TheGame::Instance() -> changeGameState( PLAY, 0 );
    }
  } else if( transitionType_ == SPLASH ) {
    frameNum_ --;
    //printf( "here\n" )
    if( frameNum_ <= 0 ) {
      TheGame::Instance() -> changeGameState( MENU, 0 );
    }
  }
  
    
}


void TransitionState::render() {
  //printf( "rendering transition state\n" );
  
  if( transitionType_ == LOADLEVEL ) {
    TheTextures::Instance() -> drawFont( displayText_, 40, "white", 10, 10, 100, 100, true );
  } else if( transitionType_ == GAMEOVER ) {
    TheTextures::Instance() -> drawFont( displayText_, 40, "white", 10, 10, 100, 100, true );
  } else if( transitionType_ == SPLASH ) {
    TheTextures::Instance() -> drawFont( displayText_, 40, "white", 350, 350, 100, 100, true );
  }
  
}

bool TransitionState::onExit() {

  return true;
}
