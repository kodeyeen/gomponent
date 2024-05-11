cmake_minimum_required(VERSION 3.19)
project(Go LANGUAGES C CXX VERSION 0.0.1)

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
	"api/Actor.cpp"
	"api/Checkpoint.cpp"
	"api/Class.cpp"
	"api/Config.cpp"
	"api/CustomModel.cpp"
	"api/GangZone.cpp"
	"api/Menu.cpp"
	"api/Object.cpp"
	"api/Pickup.cpp"
	"api/Player.cpp"
	"api/Server.cpp"
	"api/TextDraw.cpp"
	"api/TextLabel.cpp"
	"api/Vehicle.cpp"
	"api/api.cpp"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OMP-SDK
)

