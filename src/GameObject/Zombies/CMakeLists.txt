cmake_minimum_required(VERSION 3.16)

add_library(
	Zombies
	STATIC
	common_zombie.cpp
)


target_link_libraries(
  Zombies
  GameObject
  GameWorld
)

target_include_directories(
  Plants
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/GameWorld/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
)
