#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <vector>
#include <string>
#include "SDL.h"

struct Path {
  int x;
  int y;
  Path( int p_x, int p_y ) : x( p_x ), y( p_y ) {}
};

struct AnimationData {
  int     minFrame        = 0;
  int     maxFrame        = 0;
  Uint32  duration        = 1000;
  int     swapFrameAfter  = 1000;
  int     swapAnimAfter   = 1000;
  bool    oscillate       = false;
};

struct StateData {
  int   spriteState;
  int   currentRow  = 1;
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
  bool  centerOffset;
  
  std::string   objectType = "unknown";
  std::string   textureID;
  std::string   filename;
  std::string   name = "noname";
  
  std::vector<StateData>  stateData;
  std::vector<Path>       pathData;
};

struct DrawFrameParams {
  std::string id;
  int   srcX;
  int   srcY;
  int   srcW;
  int   srcH;
  int   dstX;
  int   dstY;
  int   dstW;
  int   dstH;
  int   currentRow;
  int   currentFrame;
  bool  flip = false;
  int   spriteID = -1;
};

enum SpriteState {
    DEFAULT   = 0
  , MOVING    = 1
  , FIRING    = 2
  , DYING     = 3
  , DODGING   = 4
};

enum buttons {
    RIGHT = 0
  , LEFT  = 1
  , UP    = 2
  , DOWN  = 3
  , FIRE  = 4
  , DODGE = 5
  , BOMB  = 6
  , START = 7
  , QUIT  = 8
  , OK    = 9
  , BACK  = 10
};

enum lastDirection {
  DIR_LEFT, DIR_RIGHT
};

enum ProjectileTypes {
    UNDEF, PBULLET, PBOMB, EBULLET, EBOMB
};

struct ProjectileData {
  int   type;
  int   srcX;
  int   srcY;
  int   dstX;
  int   dstY;
  float speedFactor;
  bool  destroyAtDest = false;
  bool  canDamage     = true;
};

struct Hitbox {
  int left;
  int right;
  int top;
  int bottom;
};

#endif //STRUCTS_HPP
