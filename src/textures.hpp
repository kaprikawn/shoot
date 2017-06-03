#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <map>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "structs.hpp"

class Textures {
  private:
    SDL_Surface*      tempSurface_;
    SDL_Texture*      texture_;
    
    SDL_Rect          srcRect;
    SDL_Rect          dstRect;
    
    static Textures*  instance_;

    std::map<std::string, SDL_Texture*> textureMaps_;
    std::vector<std::string> loadedIDs_;
    
    Textures(){}
  public:
    
    ~Textures(){}
    
    bool load( std::string filename, std::string id, SDL_Renderer* renderer );
    void drawFrame( DrawFrameParams& params );
    
    static Textures* Instance() {
      if( instance_ == 0 ) {
        instance_ = new Textures();
      }
      return instance_;
    }
};

typedef Textures TheTextures;

#endif //TEXTURES_HPP

