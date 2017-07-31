#include <iostream>
#include <vector>
#include "inputHandler.hpp"
#include "game.hpp"

InputHandler* InputHandler::instance_ = 0;

void InputHandler::initialiseJoysticks() {
  if( SDL_WasInit( SDL_INIT_JOYSTICK ) == 0 ) {
    SDL_InitSubSystem( SDL_INIT_JOYSTICK );
  }
  
  if( SDL_NumJoysticks() > 0 ) {
    for( int i = 0; i < SDL_NumJoysticks(); i++ ) {
      SDL_Joystick* joy = SDL_JoystickOpen( i );
      if( joy == NULL ) {
        std::cout << SDL_GetError() << std::endl;
      } else {
        joysticks_.push_back( joy );
        //m_joystickValues.push_back( std::make_pair( new Vector2D( 0, 0 ), new Vector2D( 0, 0 ) ) );
        for( int b = 0; b < SDL_JoystickNumButtons( joy ); b++ ) {
          buttonStates_.push_back( false );
        }
      }
    }
    
    SDL_JoystickEventState( SDL_ENABLE );
    joysticksInitialised_ = true;
  } else {
    joysticksInitialised_ = false;
  }
  std::cout << "Initialised " << joysticks_.size()  << " joystick(s)" << std::endl;
}

void InputHandler::onKeyDown() {
  keystates_ = SDL_GetKeyboardState( NULL );
  
  if( keystates_[ SDL_SCANCODE_ESCAPE ] == 1 ) {
    TheGame::Instance() -> quit();
  }
}

void InputHandler::onKeyUp() {
  keystates_ = SDL_GetKeyboardState( NULL );
}

bool InputHandler::isKeyDown( SDL_Scancode key ) {
  if( keystates_ != 0 ) {
    if( keystates_[key] == 1 ) {
      return true;
    } else {
      return false;
    }
  }
  return false;
}

bool InputHandler::isPressed( int button ) {
  if( button == 0 ) {
    if( keystates_[ SDL_SCANCODE_RIGHT ] == 1 || keystates_[ SDL_SCANCODE_D ] == 1 || currentHat_ == SDL_HAT_RIGHT || currentHat_ == SDL_HAT_RIGHTUP || currentHat_ == SDL_HAT_RIGHTDOWN ) {
      return true;
    }
  } else if( button == 1 ) {
    if( keystates_[ SDL_SCANCODE_LEFT ] == 1 || keystates_[ SDL_SCANCODE_A ] == 1 || currentHat_ == SDL_HAT_LEFT || currentHat_ == SDL_HAT_LEFTUP || currentHat_ == SDL_HAT_LEFTDOWN ) {
      return true;
    }
  } else if( button == 2 ) {
    if( keystates_[ SDL_SCANCODE_UP ] == 1 || keystates_[ SDL_SCANCODE_W ] == 1 || currentHat_ == SDL_HAT_UP || currentHat_ == SDL_HAT_LEFTUP || currentHat_ == SDL_HAT_RIGHTUP ) {
      return true;
    }
  } else if( button == 3 ) {
    if( keystates_[ SDL_SCANCODE_DOWN ] == 1 || keystates_[ SDL_SCANCODE_S ] == 1 || currentHat_ == SDL_HAT_DOWN || currentHat_ == SDL_HAT_LEFTDOWN || currentHat_ == SDL_HAT_RIGHTDOWN ) {
      return true;
    }
  } else if( button == 4 ) { // fire
    if( keystates_[ SDL_SCANCODE_Z ] == 1 || keystates_[ SDL_SCANCODE_SPACE ] == 1  ) {
      return true;
    }
    if( gamepadsInitialised_ ) {
      if( buttonStates_[ 2 ] ) {
        return true;
      }
    }
  } else if( button == 5 ) { // roll
    if( keystates_[ SDL_SCANCODE_X ] == 1 || keystates_[ SDL_SCANCODE_LSHIFT ] == 1 ) {
      return true;
    }
  } else if( button == 6 ) { // bomb
    if( keystates_[ SDL_SCANCODE_C ] == 1 || keystates_[ SDL_SCANCODE_LCTRL ] ) {
      return true;
    }
  }
  /*else if( button == 7 ) { // start
    if( keystates_[ SDL_SCANCODE_S ] == 1 ) {
      return true;
    }
  } else if( button == 8 ) { // quit
    if( keystates_[ SDL_SCANCODE_Q ] == 1 ) {
      return true;
    }
  } else if( button == 9 ) { // ok
    if( keystates_[ SDL_SCANCODE_O ] == 1 ) {
      return true;
    }
  } else if( button == 10 ) { // back
    if( keystates_[ SDL_SCANCODE_BACKSPACE ] == 1 ) {
      return true;
    }
  }*/
  
  return false;
}

void InputHandler::onHatMotion( SDL_Event &event ) {
  
  if( !joysticksInitialised_ ) {
    return;
  }
  
  for( unsigned int i = 0; i < joysticks_.size(); i++ ) {
    currentHat_ = SDL_JoystickGetHat( joysticks_[i], 0 );
  }
}

void InputHandler::update() {
  SDL_Event event;
  while( SDL_PollEvent( &event ) ) {
    switch( event.type ) {
      case SDL_QUIT:
        TheGame::Instance() -> quit(); break;
      case SDL_KEYDOWN:
        onKeyDown(); break;
      case SDL_KEYUP:
        onKeyUp(); break;
      case SDL_JOYHATMOTION:
        onHatMotion( event ); break;
      case SDL_JOYBUTTONDOWN:
        whichOne_ = event.jaxis.which;
        buttonStates_[ event.jbutton.button ] = true;
        //printf( "%d pressed\n", event.jbutton.button );
        break;
      case SDL_JOYBUTTONUP:
        whichOne_ = event.jaxis.which;
        buttonStates_[ event.jbutton.button ] = false;
        break;
      default:
        break;
    }
  }
}

void InputHandler::clean() {
  if( gamepadsInitialised_ ) {
    for( int i = 0; i < SDL_NumJoysticks(); i++ ) {
      SDL_JoystickClose( joysticks_[i] );
    }
  }
}
