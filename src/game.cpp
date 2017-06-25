#include <iostream>
#include "game.hpp"
#include "inputHandler.hpp"
#include "playState.hpp"
#include "values.hpp"

Game* Game::instance_ = 0;

bool Game::init( const char* title, int xpos, int ypos, int width, int height, int flags ) {
  
  if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) != 0 ) {
    std::cout << "Failed to load SDL : " << SDL_GetError() << std::endl;
    return false;
  }
  
  window_ = SDL_CreateWindow( title, xpos, ypos, width, height, flags );
  if( !window_ ) {
    std::cout << "Failed to create window : " << SDL_GetError() << std::endl;
    return false;
  }
  
  Uint32 renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  renderer_ = SDL_CreateRenderer( window_, -1, renderFlags );
  if( !renderer_ ) {
    std::cout << "Failed to create renderer : " << SDL_GetError() << std::endl;
    return false;
  }
  
  SDL_SetRenderDrawColor( renderer_, 102, 204, 255, 255 );
  TheInputHandler::Instance() -> initialiseJoysticks();
  TheValues::Instance() -> init();
  
  gameStateMachine_ = new GameStateMachine();
  gameStateMachine_ -> changeState( new PlayState() );
  
  running_ = true;
  
  return true;
}
void Game::handleInputs() {
  TheInputHandler::Instance() -> update();
}

void Game::update( float dt, Uint32 msFrameDiff ) {
  gameStateMachine_ -> update( dt, msFrameDiff );
}

void Game::render() {
  SDL_RenderClear( renderer_ );
  
  gameStateMachine_ -> render();
  
  SDL_RenderPresent( renderer_ );
}

void Game::clean() {
TheInputHandler::Instance() -> clean();
  SDL_DestroyWindow( window_ );
  SDL_DestroyRenderer( renderer_ );
  
  window_   = nullptr;
  renderer_ = nullptr;
}

void Game::quit() {
  TheGame::Instance() -> clean();
  std::cout << "Killing SDL" << std::endl;
  SDL_Quit();
  running_ = false;
}
