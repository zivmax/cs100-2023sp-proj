cmake_minimum_required(VERSION 3.16)

set(FREEGLUT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third_party/freeglut/include")

add_library(
  Framework
  STATIC
  ObjectBase.hpp
  ObjectBase.cpp
  WorldBase.hpp
  WorldBase.cpp
  GameManager.hpp
  GameManager.cpp
  SpriteManager.hpp
  SpriteManager.cpp
  ${CMAKE_SOURCE_DIR}/src/utils.hpp
)

target_link_libraries(
  Framework
  freeglut
  SOIL
  ToolKit
)

target_include_directories(
  Framework
  PUBLIC 
  ${FREEGLUT_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
  ${CMAKE_SOURCE_DIR}/src/ToolKit/
)
