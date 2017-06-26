#include <iostream>
#include <sstream>
#include "menuState.hpp"
#include "values.hpp"
#include "textures.hpp"
#include "game.hpp"
#include "inputHandler.hpp"

const std::string MenuState::s_menuID = "MENU";

bool MenuState::onEnter() {
  
  
  
  return true;
}

void MenuState::handleInput() {
  
  if( TheInputHandler::Instance() -> isPressed( FIRE ) ) {
    TheGame::Instance() -> changeGameState( TRANSITION, LOADLEVEL );
  }
  
}

void MenuState::update( float dt, Uint32 msFrameDiff ) {
  
  MenuState::handleInput();
    
}


void MenuState::render() {
  
}

bool MenuState::onExit() {

  return true;
}
