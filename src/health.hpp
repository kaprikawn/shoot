#ifndef HEALTH_HPP
#define HEALTH_HPP

#include <iostream>

class Health {
  
  private:
    int     hp_;
    int     max_hp_;
    Uint32  invCounter_ = 0;
  
  public:
    Health( int hp ) {
      hp_ = max_hp_ = hp;
    }
    
    void setInitialHp( int hp ) {
      hp_ = max_hp_ = hp;
    }
    
    void reduceHp( int attackAmount ) {
      if( invCounter_ == 0 ) {
        hp_ -= attackAmount;
      }
    }
    
    int getCurrentHp() {
      return hp_;
    }
    
    int getMaxHp() {
      return max_hp_;
    }
    
    void setInvCounter( Uint32 invCounter ) {
      invCounter_ = invCounter;
    }
    
    void setHp( int hp ) {
      hp_ = hp;
    }
    
    void cycleInvCounter( Uint32 msFrameDiff ) {
      if( invCounter_ != 0 ) {
        
        if( msFrameDiff >= invCounter_ ) {
          invCounter_ = 0;
        } else {
          invCounter_ -= msFrameDiff;
        }
        std::cout << "invCounter is now " << invCounter_ << std::endl;
      }
    }
    
    Uint32 getInvCounter() { return invCounter_; }
};

#endif //HEALTH_HPP

