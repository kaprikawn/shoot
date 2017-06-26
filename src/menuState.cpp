#include <iostream>
#include <sstream>
#include "menuState.hpp"
#include "values.hpp"
#include "textures.hpp"
#include "game.hpp"
#include "inputHandler.hpp"

const std::string MenuState::s_menuID = "MENU";

bool MenuState::onEnter() {
  
  TheTextures::Instance() -> load( "assets/menuMain.png", "menuMain" );
  TheTextures::Instance() -> load( "assets/iconPlay.png", "iconPlay" );
  TheTextures::Instance() -> load( "assets/iconQuit.png", "iconQuit" );
  
  playRenderParams_.id = "iconPlay";
  playRenderParams_.currentFrame = 0;
  playRenderParams_.currentRow = 1;
  playRenderParams_.srcX = 0;
  playRenderParams_.srcY = 0;
  playRenderParams_.srcW = 291;
  playRenderParams_.srcH = 132;
  playRenderParams_.dstX = 400;
  playRenderParams_.dstY = 400;
  playRenderParams_.dstW = 291;
  playRenderParams_.dstH = 132;
  
  quitRenderParams_.id = "iconQuit";
  quitRenderParams_.currentFrame = 1;
  quitRenderParams_.currentRow = 1;
  quitRenderParams_.srcX = 0;
  quitRenderParams_.srcY = 0;
  quitRenderParams_.srcW = 296;
  quitRenderParams_.srcH = 129;
  quitRenderParams_.dstX = 400;
  quitRenderParams_.dstY = 550;
  quitRenderParams_.dstW = 296;
  quitRenderParams_.dstH = 129;
  
  return true;
}

void MenuState::handleInput() {
  
  if( TheInputHandler::Instance() -> isPressed( FIRE ) ) {
    if( playSelected_ ) {
      TheGame::Instance() -> changeGameState( TRANSITION, LOADLEVEL );
    } else { // quit selected
      TheGame::Instance() -> quit();
    }
  } else if( TheInputHandler::Instance() -> isPressed( DOWN ) ) {
    playRenderParams_.currentFrame = 1;
    quitRenderParams_.currentFrame = 0;
    playSelected_ = false; // quit selected
  } else if( TheInputHandler::Instance() -> isPressed( UP ) ) {
    playRenderParams_.currentFrame = 0;
    quitRenderParams_.currentFrame = 1;
    playSelected_ = true; // quit selected
  }
  
  
  
}

void MenuState::update( float dt, Uint32 msFrameDiff ) {
  
  MenuState::handleInput();
  
  
  
  
}


void MenuState::render() {
  
  TheTextures::Instance() -> draw( "menuMain", 0, 0, 1280, 720 );
  
  
  
  TheTextures::Instance() -> drawFrame( playRenderParams_ );
  TheTextures::Instance() -> drawFrame( quitRenderParams_ );
}

bool MenuState::onExit() {

  return true;
}
