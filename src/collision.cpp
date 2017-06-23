#include "collision.hpp"

bool spritesCollided( Sprite* sA, Sprite* sB ) {
  int leftA   = sA -> getPosition().getHitbox().left;
  int rightA  = sA -> getPosition().getHitbox().right;
  int topA    = sA -> getPosition().getHitbox().top;
  int bottomA = sA -> getPosition().getHitbox().bottom;
  
  int leftB   = sB -> getPosition().getHitbox().left;
  int rightB  = sB -> getPosition().getHitbox().right;
  int topB    = sB -> getPosition().getHitbox().top;
  int bottomB = sB -> getPosition().getHitbox().bottom;
  
  // If any of the sides from A are outside of B
  if( bottomA <= topB ) { return false; }
  if( topA >= bottomB ) { return false; }
  if( rightA <= leftB ) { return false; }
  if( leftA >= rightB ) { return false; }
  
  return true;
}

std::vector<std::pair<Sprite*, Sprite*> > Collision::getCollisions( std::vector<Sprite*>& sprites, int& spritesSize ) {
  
  collisions_.clear();
  
  for( int A = 0; A < spritesSize; A++ ) {
    for( int B = 0; B < spritesSize; B++ ) {
      if( A < B && sprites[A] -> getObjectType() != "PBullet" && sprites[B] -> getObjectType() != "PBullet" ) {
        if( spritesCollided( sprites[A], sprites[B] ) ) {
          collisions_.push_back( std::make_pair( sprites[A], sprites[B] ) );
        }
      }
    }
  }
  
  return collisions_;
}
