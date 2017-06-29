#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "jsonLoader.hpp"
#include "json.hpp"
#include "textures.hpp"
#include "game.hpp"
#include "values.hpp"

void loadProjectiles( nlohmann::json p, std::vector<std::unique_ptr<ObjectData>>& projectileObjectsData ) {
  
  //nlohmann::json j = p[ "projectiles" ];
  
  for( nlohmann::json::iterator it1 = p.begin(); it1 != p.end(); ++it1 ) {
    nlohmann::json p = *it1;
    
    std::unique_ptr<ObjectData> newObjectData ( new ObjectData );
    
    newObjectData -> objectType     = p[ "objectType" ];
    newObjectData -> objectTypeSub  = p[ "objectTypeSub" ];
    newObjectData -> height         = p[ "height" ];
    newObjectData -> width          = p[ "width" ];
    newObjectData -> hb_l_offset    = p[ "hb_l_offset" ];
    newObjectData -> hb_r_offset    = p[ "hb_r_offset" ];
    newObjectData -> hb_t_offset    = p[ "hb_t_offset" ];
    newObjectData -> hb_b_offset    = p[ "hb_b_offset" ];
    newObjectData -> textureID      = p[ "textureID" ];
    newObjectData -> filename       = p[ "filename" ];
    newObjectData -> hp             = p[ "hp" ];
    newObjectData -> speed          = p[ "speed" ];
    newObjectData -> dtAdjust       = p[ "dtAdjust" ];
    
    //std::cout << "loading file " << p[ "filename" ] << " with textureID " << p[ "textureID" ] << std::endl;
    TheTextures::Instance() -> load( p[ "filename" ], p[ "textureID" ] );
    
    nlohmann::json sdRoot = p[ "stateData" ];
    
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
          //if( p[ "objectTypeSub" ] == "projectileEnemyChucker" ) {
          //  printf( "pushing back anim data\n" );
          //}
        }
      }
      newObjectData -> stateData.push_back( newStateData );
    }
    //std::cout << "loading projectile " << newObjectData -> objectTypeSub << std::endl;
    projectileObjectsData.push_back( std::move( newObjectData ) );
  }
}

void JsonLoader::loadDataMain( std::vector<std::unique_ptr<ObjectData>>& commonObjectsData, std::vector<std::unique_ptr<ObjectData>>& projectileObjectsData ) {

  std::ifstream fin( "assets/dataMain.json", std::ifstream::binary );
  nlohmann::json j;
  fin >> j;
  
  nlohmann::json m = j[ "mainObjects" ]; // hero and target
  
  for( nlohmann::json::iterator it = m.begin(); it != m.end(); ++it ) {
    nlohmann::json o = *it;
    
    std::unique_ptr<ObjectData> newObjectData ( new ObjectData );
    
    newObjectData -> objectType   = o[ "objectType" ];
    newObjectData -> height       = o[ "height" ];
    newObjectData -> width        = o[ "width" ];
    newObjectData -> x            = o[ "x" ];
    newObjectData -> y            = o[ "y" ];
    newObjectData -> hb_l_offset  = o[ "hb_l_offset" ];
    newObjectData -> hb_r_offset  = o[ "hb_r_offset" ];
    newObjectData -> hb_t_offset  = o[ "hb_t_offset" ];
    newObjectData -> hb_b_offset  = o[ "hb_b_offset" ];
    newObjectData -> textureID    = o[ "textureID" ];
    newObjectData -> filename     = o[ "filename" ];
    newObjectData -> hp           = o[ "hp" ];
    newObjectData -> spawnTime    = o[ "spawnTime" ];
    newObjectData -> speed        = o[ "speed" ];
    newObjectData -> centerOffset = o[ "centerOffset" ];
    
    TheTextures::Instance() -> load( o[ "filename" ], o[ "textureID" ] );
    
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
  
  loadProjectiles( j[ "projectiles" ], projectileObjectsData );
  
}

void JsonLoader::loadLevel( int levelNumber, std::vector<std::unique_ptr<ObjectData>>& levelObjectsData, std::vector<std::unique_ptr<ObjectData>>& projectileObjectsData, std::string& backgroundFilename, int& pointsNeeded ) {

  std::stringstream ss;
  ss << "assets/dataLevel" << levelNumber << ".json";
  std::string filename = ss.str();
  
  std::ifstream fin( filename, std::ifstream::binary );
  nlohmann::json j;
  fin >> j;
  
  nlohmann::json e = j[ "enemies" ];
  for( nlohmann::json::iterator it1 = e.begin(); it1 != e.end(); ++it1 ) {
    nlohmann::json enemy = *it1;
    
    nlohmann::json spawns = enemy[ "spawns" ];
    for( nlohmann::json::iterator enemySpawn = spawns.begin(); enemySpawn != spawns.end(); ++enemySpawn ) {
      nlohmann::json eSpawn = *enemySpawn;
      
      std::unique_ptr<ObjectData> newObjectData ( new ObjectData );
      
      newObjectData -> objectType     = enemy[ "objectType" ];
      newObjectData -> objectType     = enemy[ "objectTypeSub" ];
      newObjectData -> projectileType = enemy[ "projectileType" ];
      newObjectData -> height         = enemy[ "height" ];
      newObjectData -> width          = enemy[ "width" ];
      newObjectData -> hb_l_offset    = enemy[ "hb_l_offset" ];
      newObjectData -> hb_r_offset    = enemy[ "hb_r_offset" ];
      newObjectData -> hb_t_offset    = enemy[ "hb_t_offset" ];
      newObjectData -> hb_b_offset    = enemy[ "hb_b_offset" ];
      newObjectData -> textureID      = enemy[ "textureID" ];
      newObjectData -> filename       = enemy[ "filename" ];
      newObjectData -> hp             = enemy[ "hp" ];
      newObjectData -> speed          = enemy[ "speed" ];
      newObjectData -> spawnTime      = eSpawn[ "spawnTime" ];
      newObjectData -> x              = eSpawn[ "x" ];
      newObjectData -> y              = eSpawn[ "y" ];
      
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
  
  loadProjectiles( j[ "projectiles" ], projectileObjectsData );
  
  backgroundFilename = j[ "background" ][ "filename" ];
  
  TheValues::Instance() -> updatePointsNeeded( j[ "pointsNeeded" ] );
  TheValues::Instance() -> updateCurrentLevel( j[ "currentLevel" ] );
  TheValues::Instance() -> updateCurrentStage( j[ "currentStage" ] );
  TheValues::Instance() -> updateNextLevel   ( j[ "nextLevel" ] );
  TheValues::Instance() -> updateNextStage   ( j[ "nextStage" ] );
  TheValues::Instance() -> resetPoints();
  
}

