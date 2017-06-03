#ifndef GAME_HPP
#define GAME_HPP

#include "SDL.h"
#include "gameStateMachine.hpp"

class Game {
  private:
    SDL_Window*   window_;
    SDL_Renderer* renderer_;
    float         dt_ = 0.0f;
    Uint32        msFrameDiff_ = 0;
    
    bool          running_;
    static Game*  instance_;
    
    GameStateMachine* gameStateMachine_;
    
    Game(){}
  
  public:
    ~Game(){}
    
    bool init( const char* title, int xpos, int ypos, int width, int height, int flags );
    void handleInputs();
    void update( float dt, Uint32 msFrameDiff );
    void render();
    void clean();
    void quit();
    
    bool gameRunning() { return running_; }

    static Game* Instance() {
      if( instance_ == 0 ) {
        instance_ = new Game();
      }
      return instance_;
    }
};

typedef Game TheGame;

#endif //GAME_HPP
