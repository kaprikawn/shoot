#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <map>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "structs.hpp"

class Textures {
  private:
    SDL_Surface*      tempSurface_;
    SDL_Texture*      texture_;
    SDL_Renderer*     renderer_;
    
    SDL_Rect          srcRect_;
    SDL_Rect          dstRect_;
    
    SDL_RendererFlip  flip_;
    
    static Textures*  instance_;

    std::map<std::string, SDL_Texture*> textureMaps_;
    std::vector<std::string>            loadedIDs_;
    
    std::map<int, TTF_Font*>    fonts_;
    std::vector<int>            loadedFonts_;
    
    std::map<std::string, SDL_Color> colours_;
    
    float x, xdiff, y, ydiff;
    
    Textures(){}
  public:
    
    ~Textures(){}
    
    bool load( std::string filename, std::string id );
    void drawFrame( DrawFrameParams& params );
    void draw( std::string id, int x, int y, int w, int h );
    
    bool loadFont( int fontSize );
    void loadColours();
    void drawFont( std::string text, int fontSize, std::string colour, int x, int y, int w, int h, bool fixedSize );
    
    static Textures* Instance() {
      if( instance_ == 0 ) {
        instance_ = new Textures();
      }
      return instance_;
    }
};

typedef Textures TheTextures;

#endif //TEXTURES_HPP

