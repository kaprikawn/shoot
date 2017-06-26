#include <iostream>
#include "textures.hpp"
#include "game.hpp"

Textures* Textures::instance_ = 0;

bool Textures::loadFont( int fontSize ) {
  
  if( !loadedFonts_.empty() ) {
    for( unsigned int i = 0; i < loadedFonts_.size(); i++ ) {
      if( fontSize == loadedFonts_[i] ) {
        return true; // already loaded
      }
    }
  }
  
  TTF_Font* font = TTF_OpenFont( "assets/UbuntuMono-R.ttf", fontSize );
  if( font ) {
    fonts_[ fontSize ] = font;
    loadedFonts_.push_back( fontSize );
    return true;
  }
  return false; // reaching here means something went wrong
}

void Textures::loadColours() {
  colours_[ "white" ] = { 255, 255, 255, 255 };
}

void Textures::drawFont( std::string text, int fontSize, std::string colour, int x, int y, int w, int h, bool fixedSize ) {
  
  renderer_ = TheGame::Instance() -> getRenderer();
  
  
  //SDL_SetRenderDrawColor( renderer_, 255, 255, 255, 255 );
  SDL_Surface* textSurface = TTF_RenderText_Solid( fonts_[ fontSize ], text.c_str(), colours_[ colour ] );
  SDL_Texture* textTexture = SDL_CreateTextureFromSurface( renderer_, textSurface );
  
  dstRect_.x = x;
  dstRect_.y = y;
  if( fixedSize && 1 == 2 ) {
    dstRect_.w = w;
    dstRect_.y = y;
  } else {
    SDL_QueryTexture( textTexture, NULL, NULL, &dstRect_.w, &dstRect_.h );
  }
  
  
  SDL_RenderCopy( renderer_, textTexture, NULL, &dstRect_ );
  SDL_FreeSurface( textSurface );
  
  
}

bool Textures::load( std::string filename, std::string id ) {
  if( !loadedIDs_.empty() ) {
    for( unsigned int i = 0; i < loadedIDs_.size(); i++ ) {
      if( id == loadedIDs_[i] ) {
        return true;  // already loaded
      }
    }
  }
  
  tempSurface_ = IMG_Load( filename.c_str() );
  if( tempSurface_ == 0 ) { return false; }
  
  texture_ = SDL_CreateTextureFromSurface( TheGame::Instance() -> getRenderer(), tempSurface_ );
  SDL_FreeSurface( tempSurface_ );
  
  if( texture_ != 0 ) {
    textureMaps_[ id ] = texture_;
    loadedIDs_.push_back( id );
    return true;
  }
  return false; // reaching here means something went wrong
}

void Textures::draw( std::string id, int x, int y, int w, int h ) {
  srcRect_.x = dstRect_.x = x;
  srcRect_.y = dstRect_.y = y;
  srcRect_.w = dstRect_.w = w;
  srcRect_.h = dstRect_.h = h;
  
  SDL_RenderCopyEx( TheGame::Instance() -> getRenderer(), textureMaps_[ id ], &srcRect_, &dstRect_, 0, 0, SDL_FLIP_NONE );
}

void Textures::drawFrame( DrawFrameParams& params ) {
  
  //std::cout << "textures current row is " << params.currentRow << std::endl;
  
  
  
  srcRect_.x = params.srcW * params.currentFrame;
  srcRect_.y = params.srcH * ( params.currentRow - 1 );
  srcRect_.w = params.srcW;
  srcRect_.h = params.srcH;
  
  dstRect_.x = params.dstX;
  dstRect_.y = params.dstY;// + params.elevation;
  dstRect_.w = params.dstW;
  dstRect_.h = params.dstH;// * params.scale;
  
  /*if( params.spriteID == 2 ) {
    std::cout << "params.currentRow is " << params.currentRow << std::endl;
    std::cout << "srcRect_.x is " << srcRect_.x << std::endl;
    std::cout << "srcRect_.y is " << srcRect_.y << std::endl;
    std::cout << "srcRect_.w is " << srcRect_.w << std::endl;
    std::cout << "srcRect_.h is " << srcRect_.h << std::endl;
  }*/
  
  if( params.flip ) {
    flip_ = SDL_FLIP_HORIZONTAL;
  } else {
    flip_ = SDL_FLIP_NONE;
  }
  
  SDL_RenderCopyEx( TheGame::Instance() -> getRenderer(), textureMaps_[ params.id ], &srcRect_, &dstRect_, 0, 0, flip_ );
  
}

