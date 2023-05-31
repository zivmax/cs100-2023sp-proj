cmake_minimum_required(VERSION 3.16)

add_library(
	Etc
	STATIC
	etc.hpp
)


target_link_libraries(
	Etc
	Framework
	GameObject
)

target_include_directories(
	Etc
	PUBLIC 
	${CMAKE_SOURCE_DIR}/src/GameWorld/
	${CMAKE_SOURCE_DIR}/src/GameObject/
	${CMAKE_SOURCE_DIR}/src/Framework/
)
