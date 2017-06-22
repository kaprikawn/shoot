#include <iostream>
#include <fstream>
#include "jsonLoader.hpp"
#include "json.hpp"
#include "textures.hpp"
#include "game.hpp"

std::vector<ObjectData*> JsonLoader::getObjectData( std::string filename ) {
  std::ifstream fin( filename, std::ifstream::binary );
  nlohmann::json j;
  fin >> j;
  
  for( nlohmann::json::iterator it = j.begin(); it != j.end(); ++it ) {
    nlohmann::json o = *it;
    
    ObjectData* newObjectData = new ObjectData();
    
    newObjectData -> objectType        = o[ "properties" ][ "objectType" ];
    newObjectData -> height            = o[ "properties" ][ "height" ];
    newObjectData -> width             = o[ "properties" ][ "width" ];
    newObjectData -> x                 = o[ "properties" ][ "x" ];
    newObjectData -> y                 = o[ "properties" ][ "y" ];
    newObjectData -> hb_left_adjust    = o[ "properties" ][ "hb_left_adjust" ];
    newObjectData -> hb_right_adjust   = o[ "properties" ][ "hb_right_adjust" ];
    newObjectData -> hb_top_adjust     = o[ "properties" ][ "hb_top_adjust" ];
    newObjectData -> hb_bottom_adjust  = o[ "properties" ][ "hb_bottom_adjust" ];
    newObjectData -> textureID         = o[ "properties" ][ "textureID" ];
    newObjectData -> filename          = o[ "properties" ][ "filename" ];
    newObjectData -> hp                = o[ "properties" ][ "hp" ];
    newObjectData -> spawnTime         = o[ "properties" ][ "spawnTime" ];
    newObjectData -> speed             = o[ "properties" ][ "speed" ];
    newObjectData -> centerOffset      = o[ "properties" ][ "centerOffset" ];
    
    TheTextures::Instance() -> load( o[ "properties" ][ "filename" ], o[ "properties" ][ "textureID" ] );
    
    nlohmann::json sdRoot           = o[ "stateData" ];
    
    for( nlohmann::json::iterator sd1 = sdRoot.begin(); sd1 != sdRoot.end(); ++sd1 ) {
      nlohmann::json sd = *sd1;
      
      StateData newStateData;
      
      newStateData.spriteState   = sd[ "spriteState" ];
      
      if( !sd[ "skip" ] ) {
        newStateData.id         = sd[ "id" ];
        newStateData.fixedAnim  = sd[ "fixedAnim" ];
        nlohmann::json aRoot    = sd[ "animation" ];
        
        for( nlohmann::json::iterator a1 = aRoot.begin(); a1 != aRoot.end(); ++a1 ) {
          nlohmann::json a = *a1;
          AnimationData newAnimationData;
          
          newAnimationData.minFrame       = a[ "minFrame" ];
          newAnimationData.maxFrame       = a[ "maxFrame" ];
          newAnimationData.currentRow     = a[ "currentRow" ];
          newAnimationData.duration       = a[ "duration" ];
          newAnimationData.swapFrameAfter = a[ "swapFrameAfter" ];
          newAnimationData.swapAnimAfter  = a[ "swapAnimAfter" ];
          newAnimationData.oscillate      = a[ "oscillate" ];
          
          
          newStateData.animData.push_back( newAnimationData );
          //printf( "pushing back anim data\n" );
        }
      }
      newObjectData -> stateData.push_back( newStateData );
      
    }
    
    if( newObjectData -> objectType == "Enemy" ) {
      nlohmann::json pathRoot = o[ "pathData" ];
      for( nlohmann::json::iterator pd1 = pathRoot.begin(); pd1 != pathRoot.end(); ++pd1 ) {
        nlohmann::json pd = *pd1;
        Path newPathData( pd[ "x" ], pd[ "y" ] );
        newObjectData -> pathData.push_back( newPathData );
      }
    }
    
    returnData_.push_back( newObjectData );
    
  
  }
  
  return returnData_;
}
