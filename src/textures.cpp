#include <iostream>
#include "textures.hpp"
#include "SDL_image.h"
#include "game.hpp"

Textures* Textures::instance_ = 0;

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
  }
  return false; // reaching here means something went wrong
}

void Textures::draw( std::string id, int x, int y, int w, int h ) {
  srcRect.x = dstRect.x = x;
  srcRect.y = dstRect.y = y;
  srcRect.w = dstRect.w = w;
  srcRect.h = dstRect.h = h;
  
  SDL_RenderCopyEx( TheGame::Instance() -> getRenderer(), textureMaps_[ id ], &srcRect, &dstRect, 0, 0, SDL_FLIP_NONE );
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
  
  if( params.flip ) {
    flip_ = SDL_FLIP_HORIZONTAL;
  } else {
    flip_ = SDL_FLIP_NONE;
  }
  
  SDL_RenderCopyEx( TheGame::Instance() -> getRenderer(), textureMaps_[ params.id ], &srcRect, &dstRect, 0, 0, flip_ );
  
}

