cmake_minimum_required( VERSION 3.30 ) # Minimum required version of cmake for the project to build

project (
	weather_monitoring
	VERSION 0.0.1
	LANGUAGES CXX
	) # Create project information

set(CMAKE_CXX_STANDARD 23) # Set C++ standard to 23
set(CMAKE_CXX_STANDARD_REQUIRED 23)

file( GLOB_RECURSE files ./**.cpp ) # Find all .cpp files and save them int o variable "files"

add_executable( main ../main.cpp ${files} ) # Build the executable from main.cpp and load files saved in variable "files"
target_include_directories( main PRIVATE ../include ) # Include all necessary headers
