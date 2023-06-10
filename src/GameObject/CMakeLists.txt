cmake_minimum_required(VERSION 3.16)

message("Call GameObject")

add_library(
	GameObject
	STATIC
	GameObject.hpp
	GameObject.cpp
 )


add_subdirectory(./Plants/)
add_subdirectory(./Seeds/)
add_subdirectory(./Zombies/)
add_subdirectory(./Etc/)


target_link_libraries(
	GameObject
	Framework
	ToolKit
)


target_include_directories(
	GameObject
	PUBLIC 
	${CMAKE_SOURCE_DIR}/src/
	${CMAKE_SOURCE_DIR}/src/Framework/
	${CMAKE_SOURCE_DIR}/src/GameObject/
	${CMAKE_SOURCE_DIR}/src/GameWorld/
	${CMAKE_SOURCE_DIR}/src/GameObject/ToolKit/
)

