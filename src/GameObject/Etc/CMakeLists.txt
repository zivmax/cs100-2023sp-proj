cmake_minimum_required(VERSION 3.16)

message("Call Etc")

file(GLOB MY_SOURCE_FILES
    *.cpp
    *.h
)

add_library(
	Etc
	STATIC
	${MY_SOURCE_FILES}
)


target_link_libraries(
	Etc
	GameObject
)

target_include_directories(
	Etc
	PUBLIC 
	${CMAKE_SOURCE_DIR}/src/
	${CMAKE_SOURCE_DIR}/src/Framework/
	${CMAKE_SOURCE_DIR}/src/GameObject/
	${CMAKE_SOURCE_DIR}/src/GameWorld/
	${CMAKE_SOURCE_DIR}/src/GameObject/Zombies/
	${CMAKE_SOURCE_DIR}/src/GameObject/Plants/
	${CMAKE_SOURCE_DIR}/src/GameObject/Etc/
)
