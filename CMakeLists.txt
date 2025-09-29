# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(FileServer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)


# Include directories

###################################注意顺序###########################
# Add subdirectory for src
add_subdirectory(tool)
add_subdirectory(src)

#target_link_libraries(FileServer PRIVATE ToolLib)
