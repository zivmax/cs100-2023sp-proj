cmake_minimum_required(VERSION 3.16)

message("Call Zombies")

file(GLOB MY_SOURCE_FILES
    "*.cpp"
    "*.h"
)

add_library(
	Zombies
	STATIC
	${MY_SOURCE_FILES}
)


target_link_libraries(
	Zombies
	GameObject
	etc
)

target_include_directories(
	Zombies
	PUBLIC 
	${CMAKE_SOURCE_DIR}/src/
	${CMAKE_SOURCE_DIR}/src/Framework/
	${CMAKE_SOURCE_DIR}/src/GameObject/
	${CMAKE_SOURCE_DIR}/src/GameWorld/
	${CMAKE_SOURCE_DIR}/src/GameObject/Zombies/
	${CMAKE_SOURCE_DIR}/src/GameObject/Etc/
)
