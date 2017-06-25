#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "jsonLoader.hpp"
#include "json.hpp"
#include "textures.hpp"
#include "game.hpp"

void JsonLoader::loadDataMain( std::vector<std::unique_ptr<ObjectData>>& commonObjectsData ) {

  std::ifstream fin( "assets/dataMain.json", std::ifstream::binary );
  nlohmann::json j;
  fin >> j;
  
  for( nlohmann::json::iterator it = j.begin(); it != j.end(); ++it ) {
    nlohmann::json o = *it;
    
    std::unique_ptr<ObjectData> newObjectData ( new ObjectData );
    
    newObjectData -> objectType   = o[ "properties" ][ "objectType" ];
    newObjectData -> height       = o[ "properties" ][ "height" ];
    newObjectData -> width        = o[ "properties" ][ "width" ];
    newObjectData -> x            = o[ "properties" ][ "x" ];
    newObjectData -> y            = o[ "properties" ][ "y" ];
    newObjectData -> hb_l_offset  = o[ "properties" ][ "hb_l_offset" ];
    newObjectData -> hb_r_offset  = o[ "properties" ][ "hb_r_offset" ];
    newObjectData -> hb_t_offset  = o[ "properties" ][ "hb_t_offset" ];
    newObjectData -> hb_b_offset  = o[ "properties" ][ "hb_b_offset" ];
    newObjectData -> textureID    = o[ "properties" ][ "textureID" ];
    newObjectData -> filename     = o[ "properties" ][ "filename" ];
    newObjectData -> hp           = o[ "properties" ][ "hp" ];
    newObjectData -> spawnTime    = o[ "properties" ][ "spawnTime" ];
    newObjectData -> speed        = o[ "properties" ][ "speed" ];
    newObjectData -> centerOffset = o[ "properties" ][ "centerOffset" ];
    
    TheTextures::Instance() -> load( o[ "properties" ][ "filename" ], o[ "properties" ][ "textureID" ] );
    
    nlohmann::json sdRoot = o[ "stateData" ];
    
    for( nlohmann::json::iterator sd1 = sdRoot.begin(); sd1 != sdRoot.end(); ++sd1 ) {
      nlohmann::json sd = *sd1;
      
      StateData newStateData;
      
      newStateData.spriteState   = sd[ "spriteState" ];
      
      if( !sd[ "skip" ] ) {
        newStateData.id         = sd[ "id" ];
        newStateData.currentRow = sd[ "currentRow" ];
        newStateData.fixedAnim  = sd[ "fixedAnim" ];
        nlohmann::json aRoot    = sd[ "animation" ];
        
        for( nlohmann::json::iterator a1 = aRoot.begin(); a1 != aRoot.end(); ++a1 ) {
          nlohmann::json a = *a1;
          AnimationData newAnimationData;
          
          newAnimationData.minFrame       = a[ "minFrame" ];
          newAnimationData.maxFrame       = a[ "maxFrame" ];
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
    
    commonObjectsData.push_back( std::move( newObjectData ) );
  }
}

void JsonLoader::loadLevel( int levelNumber, std::vector<std::unique_ptr<ObjectData>>& levelObjectsData, std::string& backgroundFilename, int& pointsNeeded ) {

  std::stringstream ss;
  ss << "assets/dataLevel" << levelNumber << ".json";
  std::string filename = ss.str();
  
  std::ifstream fin( filename, std::ifstream::binary );
  nlohmann::json j;
  fin >> j;
  
  backgroundFilename  = j[ "background" ][ "filename" ];
  pointsNeeded        = j[ "pointsNeeded" ];
  
  nlohmann::json e = j[ "enemies" ];
  for( nlohmann::json::iterator it1 = e.begin(); it1 != e.end(); ++it1 ) {
    nlohmann::json enemy = *it1;
    
    nlohmann::json spawns = enemy[ "spawns" ];
    for( nlohmann::json::iterator enemySpawn = spawns.begin(); enemySpawn != spawns.end(); ++enemySpawn ) {
      nlohmann::json eSpawn = *enemySpawn;
      
      std::unique_ptr<ObjectData> newObjectData ( new ObjectData );
      
      newObjectData -> objectType   = enemy[ "objectType" ];
      newObjectData -> height       = enemy[ "height" ];
      newObjectData -> width        = enemy[ "width" ];
      newObjectData -> hb_l_offset  = enemy[ "hb_l_offset" ];
      newObjectData -> hb_r_offset  = enemy[ "hb_r_offset" ];
      newObjectData -> hb_t_offset  = enemy[ "hb_t_offset" ];
      newObjectData -> hb_b_offset  = enemy[ "hb_b_offset" ];
      newObjectData -> textureID    = enemy[ "textureID" ];
      newObjectData -> filename     = enemy[ "filename" ];
      newObjectData -> hp           = enemy[ "hp" ];
      newObjectData -> speed        = enemy[ "speed" ];
      newObjectData -> spawnTime    = eSpawn[ "spawnTime" ];
      newObjectData -> x            = eSpawn[ "x" ];
      newObjectData -> y            = eSpawn[ "y" ];
      
      TheTextures::Instance() -> load( enemy[ "filename" ], enemy[ "textureID" ] );
      
      nlohmann::json sdRoot         = enemy[ "stateData" ];
      
      for( nlohmann::json::iterator sd1 = sdRoot.begin(); sd1 != sdRoot.end(); ++sd1 ) {
        nlohmann::json sd = *sd1;
        
        StateData newStateData;
        
        newStateData.spriteState   = sd[ "spriteState" ];
        
        if( !sd[ "skip" ] ) {
          newStateData.id         = sd[ "id" ];
          newStateData.currentRow = sd[ "currentRow" ];
          newStateData.fixedAnim  = sd[ "fixedAnim" ];
          nlohmann::json aRoot    = sd[ "animation" ];
          
          for( nlohmann::json::iterator a1 = aRoot.begin(); a1 != aRoot.end(); ++a1 ) {
            nlohmann::json a = *a1;
            AnimationData newAnimationData;
            
            newAnimationData.minFrame       = a[ "minFrame" ];
            newAnimationData.maxFrame       = a[ "maxFrame" ];
            newAnimationData.duration       = a[ "duration" ];
            newAnimationData.swapFrameAfter = a[ "swapFrameAfter" ];
            newAnimationData.swapAnimAfter  = a[ "swapAnimAfter" ];
            newAnimationData.oscillate      = a[ "oscillate" ];
            
            newStateData.animData.push_back( newAnimationData );
          }
        }
        newObjectData -> stateData.push_back( newStateData );
        
      }
      
      nlohmann::json pathRoot = eSpawn [ "pathData" ];
      for( nlohmann::json::iterator pd1 = pathRoot.begin(); pd1 != pathRoot.end(); ++pd1 ) {
        nlohmann::json pd = *pd1;
        Path newPathData( pd[ "x" ], pd[ "y" ] );
        newObjectData -> pathData.push_back( newPathData );
      }
      
      levelObjectsData.push_back( std::move( newObjectData ) );
    }
  }
}

