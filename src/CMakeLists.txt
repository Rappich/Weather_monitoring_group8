cmake_minimum_required( VERSION 3.30 ) # Minimum required version of cmake for the project to build

project (
	weather_monitoring_main
	VERSION 0.0.1
	LANGUAGES CXX
) # Create project information

set(CMAKE_CXX_STANDARD 23) # Set C++ standard to 23
set(CMAKE_CXX_STANDARD_REQUIRED 23)

file( GLOB_RECURSE files ./**.cpp ) # Find all .cpp files and save them int o variable "files"

# find_package( SQLite3 REQUIRED )

add_executable( main ../main.cpp ${files} ) # Build the executable from main.cpp and load files saved in variable "files"
target_include_directories( main PRIVATE ../include ) # Include all necessary headers
# target_include_directories( main PRIVATE ${SQLite3_INCLUDE_DIRS} )
# target_link_libraries( main PRIVATE ${SQLite3_LIBRARIES} )
