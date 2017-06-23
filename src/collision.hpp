#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <vector>
#include <utility>
#include "sprite.hpp"

class Collision {

  private:
    std::vector<std::pair<Sprite*, Sprite*> > collisions_;
  
  public:
    Collision(){}
    ~Collision(){}
    
    std::vector<std::pair<Sprite*, Sprite*> > getCollisions( std::vector<Sprite*>& sprites, int& spritesSize );
};

#endif //COLLISION_HPP

