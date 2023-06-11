cmake_minimum_required(VERSION 3.16)

message("Call ToolKit")

add_library(
	ToolKit
	STATIC
	ToolKit.hpp
	ToolKit.cpp
 )

target_link_libraries(
	ToolKit
)


target_include_directories(
	GameObject
	PUBLIC 
	${CMAKE_SOURCE_DIR}/src/ToolKit/
)

