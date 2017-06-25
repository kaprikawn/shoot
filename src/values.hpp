#ifndef VALUES_HPP
#define VALUES_HPP

class Values {
  private:
    
    int     lives_;
    int     bombs_;
    
    int     pointsNeeded_;
    int     points_ = 0;
    
    static Values* s_pInstance;
    
    Values(){}
  public:
    
    ~Values(){}
    
    void init();
    void reset();
    
    
    int getLives() { return lives_; }
    int getBombs() { return bombs_; }
    int getPoints() { return points_; }
    
    void updateBombs( int amount ) {
      bombs_ += amount;
      if( bombs_ < 0 ) {
        bombs_ = 0;
      }
    }
    
    void updateLives( int amount ) {
      lives_ += amount;
    }
    
    void updatePointsNeeded( int pointsNeeded ) {
      pointsNeeded_ = pointsNeeded;
    }
    
    void updatePoints( int points ) {
      printf( "adding %d points\n", points );
      points_ += points;
    }
    
    static Values* Instance() {
      if( s_pInstance == 0 ) {
        s_pInstance = new Values();
        return s_pInstance;
      }
      return s_pInstance;
    }
};

typedef Values TheValues;

#endif //VALUES_HPP

