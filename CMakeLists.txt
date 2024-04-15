cmake_minimum_required(VERSION 3.19)
project(Gomponent LANGUAGES C CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(sdk)
add_subdirectory(network)

include_directories(
	.
	events
)

add_library(${PROJECT_NAME} SHARED
	main.cpp
	Gomponent.cpp
	Gamemode.cpp
	
	"api/api.hpp"
	"api/Class.cpp"
	"api/Config.cpp"
	"api/Pickup.cpp"
	"api/Player.cpp"
	"api/Server.cpp"
	"api/TextDraw.cpp"
	"api/Vehicle.cpp"
	"api/api.cpp"
 "api/Object.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE
    OMP-SDK
)

