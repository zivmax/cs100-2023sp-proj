cmake_minimum_required(VERSION 3.16)

message("Call Seeds")

file(GLOB MY_SOURCE_FILES
    "*.cpp"
    "*.h"
)

add_library(
	Seeds
	STATIC
	${MY_SOURCE_FILES}
)


target_link_libraries(
	Seeds
	GameObject
)

target_include_directories(
	Seeds
	PUBLIC 
	${CMAKE_SOURCE_DIR}/src/
	${CMAKE_SOURCE_DIR}/src/Framework/
	${CMAKE_SOURCE_DIR}/src/GameObject/
	${CMAKE_SOURCE_DIR}/src/GameWorld/
	${CMAKE_SOURCE_DIR}/src/GameObject/Seeds/
	${CMAKE_SOURCE_DIR}/src/GameObject/Etc/
)
