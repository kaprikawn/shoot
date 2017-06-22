#include <iostream>
#include <vector>
#include <algorithm>
#include "playState.hpp"
#include "jsonLoader.hpp"
#include "structs.hpp"
#include "textures.hpp"
#include "projectile.hpp"
#include "enemy.hpp"

const std::string PlayState::s_playID = "PLAY";

void PlayState::add( Sprite* sprite ) {
  sprites_.push_back( sprite );
  spritesSize_ = sprites_.size();
}

bool PlayState::onEnter() {
  JsonLoader jsonLoader;
  std::vector<ObjectData*> objectData = jsonLoader.getObjectData( "assets/dataMain.json" );
  
  for( unsigned int i = 0; i < objectData.size(); i++ ) {
    if( objectData[i] -> objectType == "Hero" ) {
      hero_ = new Hero( objectData[i] );
      PlayState::add( hero_ );
    } else if( objectData[i] -> objectType == "Target" ) {
      target_ = new Target( objectData[i] );
      PlayState::add( target_ );
    } else if( objectData[i] -> objectType == "Bomb" ) {
      bombObjectData_ = ( *objectData[i] );
    }
  }
  
  TheTextures::Instance() -> load( "assets/level1Background.png", "background" );
  TheTextures::Instance() -> load( "assets/bomb.png", "bomb" );
  
  PlayState::loadLevelFromFile( 1 );
  
  levelStart_ = SDL_GetTicks();
  
  return true;
}

bool PlayState::loadLevelFromFile( int currentLevel ) {
  std::vector<std::string> loadedTextures;
  bool textureLoaded = false;
  std::string currentLevelChar = std::to_string( currentLevel );
  
  JsonLoader newJsonLoader;
  std::vector<ObjectData*> objectData = newJsonLoader.getObjectData( "assets/dataLevel1.json" );
  for( unsigned int i = 0; i < objectData.size(); i++ ) {
    if( objectData[i] -> objectType == "Enemy" ) {
      enemies_.push_back( objectData[i] );
    }
    
    textureLoaded = false;
    if( !loadedTextures.empty() ) {
      for( unsigned int t = 0; t < loadedTextures.size(); t++ ) {
        if( loadedTextures[t] == objectData[i] -> textureID ) {
          textureLoaded = true;
        }
      }
    }
    
    if( !textureLoaded ) {
      if( !TheTextures::Instance() -> load( objectData[i] -> filename, objectData[i] -> textureID ) ) {
        return false;
      }
      loadedTextures.push_back( objectData[i] -> textureID );
    }
  }
  return true;
}

void PlayState::spawnProjectile( int projectileType, Sprite* originSprite ) {
  
  bombObjectData_.x = hero_ -> getMovement().getSpriteCenter().getX();
  bombObjectData_.y = hero_ -> getMovement().getSpriteCenter().getY();
  
  ProjectileData projectileData;
  
  projectileData.type = projectileType;
  projectileData.srcX = bombObjectData_.x;
  projectileData.srcY = bombObjectData_.y;
  projectileData.dstX = target_ -> getMovement().getCoordinates().getX();
  projectileData.dstY = target_ -> getMovement().getCoordinates().getY();
  
  if( projectileType == PBULLET ) {
    projectileData.speedFactor = 7.0f;
    projectileData.destroyAtDest = true;
  } else if( projectileType == PBOMB ) {
    projectileData.speedFactor = 1.8f;
  }
  
  Projectile* newProjectile = new Projectile( &bombObjectData_, projectileData );
  PlayState::add( newProjectile );
}

void PlayState::update( float dt, Uint32 msFrameDiff ) {
  for( int i = 0; i < spritesSize_; i++ ) {
    sprites_[i] -> update( dt, msFrameDiff );
    
    projectileType_ = sprites_[i] -> spawnProjectile();
    if( projectileType_ > 0 ) {
      PlayState::spawnProjectile( projectileType_, sprites_[i]  );
    }
  }
  
  //delete dead stuff
  for( unsigned i = spritesSize_; i-- > 0; ) {
    if( sprites_[i] -> needsDeleting() ) {
      //printf( "deleting %d\n", i );
      sprites_[i] -> clean();
      delete sprites_[i];
      sprites_.erase( sprites_.begin() + i );
    }
  }
  spritesSize_ = sprites_.size();
  
  currentTime_ = SDL_GetTicks();
  
  // spawn enemies
  if( !enemies_.empty() ) {
    for( unsigned i = enemies_.size(); i-- > 0; ) {
      if( !enemies_[i] -> hasSpawned && currentTime_ > ( levelStart_ + ( enemies_[i] -> spawnTime * 1000 ) ) ) {
        Enemy* newEnemy = new Enemy( enemies_[i] );
        PlayState::add( newEnemy );
        enemies_[i] -> hasSpawned = true;
      }
    }
  }
}

template<typename A, typename B> std::pair<B,A> flip_pair( const std::pair<A,B> &p) {
  return std::pair<B,A>( p.second, p.first );
}

template<typename A, typename B> std::multimap<B,A> flip_map(const std::map<A,B> &src) {
  std::multimap<B,A> dst;
  std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), 
                 flip_pair<A,B>);
  return dst;
}

void PlayState::render() {
  
  TheTextures::Instance() -> draw( "background", 0, 0, 1280, 720 );
  
  //  cpp.sh/7pky
  std::map<int, int> src; // map of draw indexes so we know which order to draw
  
  for( int i = 0; i < spritesSize_; i++ ) { // populate map
    src[i] = sprites_[i] -> getDrawIndex();
  }
  
  src[0] = 10001;
  src[1] = 10000;
  
  dst = flip_map( src ); // order by value
  
  for ( std::multimap<int, int>::iterator it=dst.begin(); it!=dst.end(); ++it ) {
    sprites_[ (*it).second ] -> render();
  }
  
  src.clear();
  dst.clear();
  
}

bool PlayState::onExit() {
  
  
  std::cout << "exiting PlayState" << std::endl;
  return true;
}
