#include <iostream>
#include "textures.hpp"
#include "SDL_image.h"
#include "game.hpp"

Textures* Textures::instance_ = 0;

bool Textures::load( std::string filename, std::string id, SDL_Renderer* renderer ) {
  if( !loadedIDs_.empty() ) {
    for( unsigned int i = 0; i < loadedIDs_.size(); i++ ) {
      if( id == loadedIDs_[i] ) {
        return true;  // already loaded
      }
    }
  }
  
  tempSurface_ = IMG_Load( filename.c_str() );
  if( tempSurface_ == 0 ) { return false; }
  
  texture_ = SDL_CreateTextureFromSurface( renderer, tempSurface_ );
  SDL_FreeSurface( tempSurface_ );
  
  if( texture_ != 0 ) {
    textureMaps_[ id ] = texture_;
    loadedIDs_.push_back( id );
  }
  return false; // reaching here means something went wrong
}

void Textures::drawFrame( DrawFrameParams& params ) {
  
  srcRect.x = params.w * params.currentFrame;
  srcRect.y = params.h * ( params.currentRow - 1 );
  srcRect.w = params.w;
  srcRect.h = params.h;
  
  dstRect.x = params.x;
  dstRect.y = params.y;
  dstRect.w = params.w * params.scale;
  dstRect.h = params.h * params.scale;
  
  SDL_RenderCopyEx( TheGame::Instance() -> getRenderer(), textureMaps_[ "hero" ], &srcRect, &dstRect, 0, 0, SDL_FLIP_NONE );
  
}

