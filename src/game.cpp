#include <iostream>
#include "game.hpp"
#include "SDL_ttf.h"
#include "inputHandler.hpp"
#include "playState.hpp"
#include "transitionState.hpp"
#include "menuState.hpp"
#include "values.hpp"
#include "textures.hpp"

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
  
  if( TTF_Init() != 0 ) {
    std::cout << "Error: could not initialise SDL TTF - " << TTF_GetError() << std::endl;
    return false;
  }
  
  TheTextures::Instance() -> loadColours();
  
  SDL_SetRenderDrawColor( renderer_, 0, 0, 0, 255 );
  TheInputHandler::Instance() -> initialiseJoysticks();
  TheValues::Instance() -> init();
  
  //gameStateMachine_ = new GameStateMachine();
  std::unique_ptr<GameStateMachine> gameStateMachine ( new GameStateMachine );
  gameStateMachine_ = std::move( gameStateMachine );
  //gameStateMachine_ = make_unique<GameState>( new GameStateMachine );
  
  
  //gameStateMachine_ -> changeState( new PlayState() );
  //std::unique_ptr<GameState> transitionState ( new TransitionState );
  
  //gameStateMachine_ -> changeState( std::move( transitionState ) );
  Game::changeGameState( TRANSITION, SPLASH );
  
  running_ = true;
  
  return true;
}

void Game::handleInputs() {
  TheInputHandler::Instance() -> update();
}

void Game::update( float dt, Uint32 msFrameDiff ) {
  if( TheValues::Instance() -> getLives() <= 0 && gameStateMachine_ -> getCurrentGameStateID() == "PLAY" ) {
    Game::changeGameState( TRANSITION, GAMEOVER );
  } else if( newState_ >= 0 ) {
    printf( "calling change state\n" );
    Game::changeGameState( newState_, transitionType_ );
  }

  gameStateMachine_ -> update( dt, msFrameDiff );
}

void Game::render() {
  SDL_RenderClear( renderer_ );
  gameStateMachine_ -> render();
  SDL_SetRenderDrawColor( renderer_, 0, 0, 0, 255 );
  SDL_RenderPresent( renderer_ );
}

void Game::setNewState( int newState, int transitionType = 0 ) {
  printf( "setting new state to %d\n", newState );
  newState_ = newState;
  transitionType_ = transitionType;
}

void Game::changeGameState( int newState, int transitionType ) {
  if( newState == PLAY ) {
    std::unique_ptr<GameState> playState ( new PlayState );
    gameStateMachine_ -> changeState( std::move( playState ) );
  } else if( newState == TRANSITION ) {
    
    std::unique_ptr<GameState> transitionState ( new TransitionState( transitionType ) );
    gameStateMachine_ -> changeState( std::move( transitionState ) );
  } else if( newState == MENU ) {
    std::unique_ptr<GameState> menuState ( new MenuState );
    gameStateMachine_ -> changeState( std::move( menuState ) );
  }
  newState_ = -1;
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
