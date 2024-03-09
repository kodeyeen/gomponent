cmake_minimum_required(VERSION 3.19)
project(Gomp LANGUAGES C CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(sdk)
add_subdirectory(network)

include_directories(
	.
	events
)

add_library(${PROJECT_NAME} SHARED
	main.cpp
	GompComponent.cpp
	Gamemode.cpp
	api.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OMP-SDK
)

