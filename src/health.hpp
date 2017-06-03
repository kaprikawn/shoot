#ifndef HEALTH_HPP
#define HEALTH_HPP

class Health {
  
  private:
    int hp_;
    int max_hp_;
  
  public:
    Health( int hp ) {
      hp_ = max_hp_ = hp;
    }
    
    void setInitialHp( int hp ) {
      hp_ = max_hp_ = hp;
    }
    
    void reduceHp( int attackAmount ) {
      hp_ -= attackAmount;
    }
    
    int getCurrentHp() {
      return hp_;
    }
    
    int getMaxHp() {
      return max_hp_;
    }
};

#endif //HEALTH_HPP

