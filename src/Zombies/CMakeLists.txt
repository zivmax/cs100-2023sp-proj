cmake_minimum_required(VERSION 3.16)

add_library(
	Zombies
	STATIC
	zombie.cpp
)


target_link_libraries(
	Zombies
	Framework
)

target_include_directories(
	Zombies
	PUBLIC 
	${CMAKE_SOURCE_DIR}/src/GameWorld/
	${CMAKE_SOURCE_DIR}/src/GameObject/
	${CMAKE_SOURCE_DIR}/src/Framework/
)
