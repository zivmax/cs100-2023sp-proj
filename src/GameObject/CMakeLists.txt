cmake_minimum_required(VERSION 3.16)

message("Call GameObject")

add_library(
	GameObject
	STATIC
	GameObject.hpp
	GameObject.cpp
 )


target_link_libraries(
	GameObject
	Framework
)



target_include_directories(
	GameObject
	PUBLIC 
	${CMAKE_SOURCE_DIR}/src/
	${CMAKE_SOURCE_DIR}/src/Framework/
	${CMAKE_SOURCE_DIR}/src/GameObject/
	${CMAKE_SOURCE_DIR}/src/GameWorld/
	${CMAKE_SOURCE_DIR}/src/GameObject/Zombies/
	${CMAKE_SOURCE_DIR}/src/GameObject/Plants/
	${CMAKE_SOURCE_DIR}/src/GameObject/Etc/
)

