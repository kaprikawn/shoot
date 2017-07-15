CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project( shoot )

add_executable( game
  inputHandler.cpp textures.cpp
  jsonLoader.cpp
  gameStateMachine.cpp playState.cpp transitionState.cpp menuState.cpp
  values.cpp hud.cpp
  animation.cpp position.cpp collision.cpp
  sprite.cpp hero.cpp target.cpp projectile.cpp enemy.cpp
  game.cpp main.cpp
)

if( WIN32 )

  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${shoot_SOURCE_DIR}/cmake")
  set(SDL2_PATH "C:\\dev\\SDL\\VC\\SDL2-2.0.5")
  set(SDL2_IMAGE_PATH "C:\\dev\\SDL\\VC\\SDL2_image-2.0.1")
  set(SDL2_TTF_PATH "C:\\dev\\SDL\\VC\\SDL2_ttf-2.0.14")
  
else()
  
  include( FindPkgConfig )

  pkg_search_module( SDL2 REQUIRED sdl2 )
  pkg_search_module( SDL2IMAGE REQUIRED SDL2_image>=2.0.0 )
  pkg_search_module( SDL2TTF REQUIRED SDL2_ttf )
endif( WIN32 )

include_directories( ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} )
target_link_libraries( game ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} )


set_property(TARGET game PROPERTY CXX_STANDARD 11)

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -g")
endif ( CMAKE_COMPILER_IS_GNUCC )

