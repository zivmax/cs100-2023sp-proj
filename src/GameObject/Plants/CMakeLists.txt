cmake_minimum_required(VERSION 3.16)

add_library(
	Plants
	STATIC
	plant.cpp	
)


target_link_libraries(
  Plants
  GameObject
  GameWorld
)

target_include_directories(
  Plants
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/GameWorld/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
)
