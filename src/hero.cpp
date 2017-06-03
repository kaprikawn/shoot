#include <iostream>
#include "hero.hpp"

Hero::Hero( ObjectData* objectData ) : Sprite( objectData ) {

}

void Hero::handleInput() {

}

void Hero::update( float dt, Uint32 msFrameDiff ) {
  Sprite::update( dt, msFrameDiff );
}

void Hero::render() {
  Sprite::render();
}

void Hero::clean() {

}
