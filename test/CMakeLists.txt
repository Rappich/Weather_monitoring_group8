cmake_minimum_required( VERSION 3.30 ) # Minimum required version of cmake for the project to build

project (
	weather_monitoring_test
	VERSION 0.0.1
	LANGUAGES CXX
) # Create project information

enable_testing()

set(CMAKE_CXX_STANDARD 23) # Set C++ standard to 23
set(CMAKE_CXX_STANDARD_REQUIRED 23)

find_package( Catch2 REQUIRED )

file( GLOB_RECURSE files ../src/**.cpp ) # Find all .cpp files and save them int o variable "files"
file( GLOB_RECURSE test_files ./**.cpp ) # Find all .cpp files and save them int o variable "files"

add_executable( test test.cpp ${files} ${test_files} ) # Build the executable from main.cpp and load files saved in variable "files"

target_include_directories( test PRIVATE ../include ) # Include all necessary headers
target_link_libraries( test PRIVATE Catch2::Catch2WithMain )

include( CTest )
include( Catch )
catch_discover_tests( test )
