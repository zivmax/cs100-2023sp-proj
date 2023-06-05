cmake_minimum_required(VERSION 3.16)

message("Call Plants")

file(GLOB MY_SOURCE_FILES
    "*.cpp"
    "*.h"
)

add_library(
	Plants
	STATIC
	${MY_SOURCE_FILES}
)



target_link_libraries(
	Plants
	GameObject
	Etc
)

target_include_directories(
	Plants
	PUBLIC 
	${CMAKE_SOURCE_DIR}/src/
	${CMAKE_SOURCE_DIR}/src/Framework/
	${CMAKE_SOURCE_DIR}/src/GameObject/
	${CMAKE_SOURCE_DIR}/src/GameWorld/
	${CMAKE_SOURCE_DIR}/src/GameObject/Plants/
	${CMAKE_SOURCE_DIR}/src/GameObject/Etc/
)
