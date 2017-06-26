#include <iostream>
#include "hud.hpp"
#include "values.hpp"
#include "game.hpp"

Hud::Hud( int pointsNeeded ) {
  pointsNeeded_ = pointsNeeded;
  
  //if( TTF_Init() == -1 ) {
  //  std::cout << "Error: could not initialise SDL TTF - " << TTF_GetError() << std::endl;
  //}
  
  font_ = TTF_OpenFont( "assets/UbuntuMono-R.ttf", 70 );
  
}

void Hud::update ( float dt, Uint32 msFrameDiff ) {

  points_ = TheValues::Instance() -> getPoints();
  
}

void Hud::render() {

  renderer_ = TheGame::Instance() -> getRenderer();
  
  ss.str( "" );
  ss << "L:" << TheValues::Instance() -> getLives() << " B:" << TheValues::Instance() -> getBombs();
  str = ss.str();
  
  msg = str.c_str();
  
  // black
  SDL_SetRenderDrawColor( renderer_, 0, 0, 0, 255 );
  rect_.x = 10;
  rect_.y = 650;
  rect_.w = 100;
  rect_.h = 50;
  SDL_RenderFillRect( renderer_, &rect_ );
  
  // grey
  SDL_SetRenderDrawColor( renderer_, 38, 38, 38, 255 );
  rect_.x += 5;
  rect_.y += 5;
  rect_.w -= 10;
  rect_.h -= 10;
  SDL_RenderFillRect( renderer_, &rect_ );
  
  
  SDL_SetRenderDrawColor( renderer_, 255, 255, 255, 255 );
  SDL_Color White = {255, 255, 255};
  SDL_Surface* textSurface_ = TTF_RenderText_Solid(  font_, msg, White );
  SDL_Texture* text_ = SDL_CreateTextureFromSurface( renderer_, textSurface_ );
  
  //SDL_Rect msg;
  rect_.x += 5;
  rect_.y += 5;
  rect_.w -= 10;
  rect_.h -= 10;
  
  SDL_RenderCopy(renderer_, text_, NULL, &rect_ );
  
  SDL_FreeSurface( textSurface_ );
  
  
  yellowWidth_  = 1260 * ( points_ / (float)pointsNeeded_ );
  redWidth_     = 1260 - yellowWidth_;
  
  SDL_SetRenderDrawColor( renderer_, 255, 255, 0, 255 );
  // yellow
  rect_.x = 10;
  rect_.y = 710;
  rect_.w = yellowWidth_;
  rect_.h = 5;
  SDL_RenderFillRect( renderer_, &rect_ );
  
  SDL_SetRenderDrawColor( renderer_, 255, 0, 0, 255 );
  // red
  rect_.x += rect_.w + 1;
  rect_.w = redWidth_;
  SDL_RenderFillRect( renderer_, &rect_ );

}

void Hud::clean () {

}
