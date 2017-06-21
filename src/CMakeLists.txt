CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project( shoot )

add_executable( game
  inputHandler.cpp textures.cpp
  jsonLoader.cpp
  gameStateMachine.cpp playState.cpp
  animation.cpp movement.cpp
  sprite.cpp hero.cpp target.cpp projectile.cpp enemy.cpp
  game.cpp main.cpp
)

include( FindPkgConfig )

pkg_search_module( SDL2 REQUIRED sdl2 )
pkg_search_module( SDL2IMAGE REQUIRED SDL2_image>=2.0.0 )

include_directories( ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} )
target_link_libraries( game ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} )


set_property(TARGET game PROPERTY CXX_STANDARD 11)

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -g")
endif ( CMAKE_COMPILER_IS_GNUCC )

