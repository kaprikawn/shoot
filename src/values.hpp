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
    
    int         currentLevel_;
    std::string currentStage_;
    int         nextLevel_    = 11;
    std::string nextStage_    = "1-1";
    
    static Values* s_pInstance;
    
    Values(){}
  public:
    
    ~Values(){}
    
    void init();
    void reset();
    
    
    int getLives()        { return lives_; }
    int getBombs()        { return bombs_; }
    int getPoints()       { return points_; }
    int getPointsNeeded() { return pointsNeeded_; }
    int getNextLevel()    { return nextLevel_; }
    
    void updateBombs( int amount ) {
      bombs_ += amount;
      if( bombs_ < 0 ) {
        bombs_ = 0;
      }
    }
    
    void updateLives( int amount ) {
      lives_ += amount;
    }
    
    // all done in json loader
    void updatePointsNeeded( int pointsNeeded ) { pointsNeeded_ = pointsNeeded; }
    void updateCurrentLevel( int currentLevel ) { currentLevel_ = currentLevel; }
    void updateCurrentStage( std::string currentStage ) { currentStage_ = currentStage; }
    void updateNextLevel( int nextLevel ) { nextLevel_ = nextLevel; }
    void updateNextStage( std::string  nextStage ) { nextStage_ = nextStage; }
    void resetPoints() { points_ = 0; }
    
    void updatePoints( int points ) {
      printf( "adding %d points\n", points );
      points_ += points;
    }
    
    std::string getCurrentStage() { return currentStage_; }
    std::string getNextStage()    { return nextStage_; }
    
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

