#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <vector>

struct Path {
  int x;
  int y;
  Path( int p_x, int p_y ) : x( p_x ), y( p_y ) {}
};

struct AnimationData {
  int   currentRow      = 1;
  int   minFrame        = 0;
  int   maxFrame        = 0;
  int   frameDelay      = 1000;
  int   swapFrameAfter  = 1000;
  int   swapAnimAfter   = 1000;
  bool  oscillate       = false;
};

struct StateData {
  int   spriteState;
  std::string id    = "NULLID";
  bool  fixedAnim   = false;
  std::vector<AnimationData> animData;
};


struct  ObjectData {
  int   spriteID;
  int   width;
  int   height;
  int   x;
  int   y;
  int   hb_left_adjust    = 0;
  int   hb_right_adjust   = 0;
  int   hb_top_adjust     = 0;
  int   hb_bottom_adjust  = 0;
  int   spawnTime         = 0;
  int   speed             = 1;
  int   hp                = 1;
  int   animDataIndex     = 0;
  bool  hasSpawned        = false;
  
  std::string   objectType;
  std::string   textureID;
  std::string   filename;
  std::string   name = "noname";
  
  std::vector<StateData>  stateData;
  std::vector<Path>       pathData;
};

struct DrawFrameParams {
  std::string id;
  int x;
  int y;
  int w;
  int h;
  float scale;
  int currentRow;
  int currentFrame;
  bool flip = false;
};


#endif //STRUCTS_HPP
