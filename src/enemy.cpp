#include <iostream>
#include "enemy.hpp"


Enemy::Enemy( ObjectData* objectData ) : Sprite( objectData ) {
  
}


void Enemy::update( float dt, Uint32 msFrameDiff ) {
  
  
  Sprite::update( dt, msFrameDiff );
  
  
}

void Enemy::render() {
  Sprite::render();
}

void Enemy::clean() {

}
