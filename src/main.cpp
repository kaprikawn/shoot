#include <iostream>
#include "SDL.h"
#include "game.hpp"

const int FPS = 60;
const float DELAY_TIME = 1000.0f / FPS;

int main( int argc, char* args[] ) {

  Uint32  currentTime_;
  Uint32  previousTime_;
  Uint32  msFrameDiff_ = 0;
  float   dt_ = 0.0f;
    
  
  if( !TheGame::Instance() -> init( "Crosshair Shooter Game", 20, 20, 1280, 720, SDL_WINDOW_SHOWN ) ) {
  //if( !TheGame::Instance() -> init( "Crosshair Shooter Game", 20, 20, 100, 100, SDL_WINDOW_SHOWN ) ) {
    std::cout << "Game initialisation failed" << std::endl;
  }

  while( TheGame::Instance() -> gameRunning() ) {
    previousTime_ = currentTime_;
    currentTime_ = SDL_GetTicks();
    msFrameDiff_ = currentTime_ - previousTime_;
    dt_ = msFrameDiff_ / 1000.0f; 
    
    TheGame::Instance() -> handleInputs();
    TheGame::Instance() -> update( dt_, msFrameDiff_ );
    TheGame::Instance() -> render();
    
    if( msFrameDiff_ < DELAY_TIME ) {
      SDL_Delay( ( DELAY_TIME - msFrameDiff_ ) );
    }
  }
  
  return 0;
}

