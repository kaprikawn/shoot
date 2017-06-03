#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <map>
#include "SDL.h"
#include "SDL_image.h"

class Textures {
  private:
    SDL_Surface*    tempSurface_;
    SDL_Texture*    texture_;
    
    SDL_Rect        srcRect;
    SDL_Rect        dstRect;
    
    static TextureManager* instance_;

    std::map<std::string, SDL_Texture*> textureMaps_;
    
    Textures(){}
  public:
    
    ~Textures(){}
    
    void init( SDL_Renderer* pRenderer );
    bool load();
    
    void drawFrame();
    
    static Textures* Instance() {
      if( instance_ == 0 ) {
        instance_ = new TextureManager();
      }
      return instance_;
    }
};

typedef Textures TheTextures;

#endif //TEXTURES_HPP

