#ifndef VALUES_HPP
#define VALUES_HPP

namespace constants {
  const int   WIDTH         = 1280;
  const int   HEIGHT        = 720;
  const int   FPS           = 60;
  const float DELAY_TIME    = 1000.0f / FPS;
}

class Values {
  private:
    
    int     lives_;
    int     bombs_;
    
    int     pointsNeeded_;
    int     points_ = 0;
    
    int         currentLevel_     = 11;
    std::string currentLevelStr_  = "1-1";
    int         nextLevel_        = 12;
    std::string nextLevelStr_     = "1-2";
    
    
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
    
    std::string getCurrentLevelStr() { return currentLevelStr_; }
    
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

