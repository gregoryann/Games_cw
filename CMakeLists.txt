cmake_minimum_required(VERSION 3.9)
#Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GamesCw)

####Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
#Output all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

####Add external dependencies ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

###Practical 1###
file(GLOB_RECURSE SOURCES pdsrc/*.cpp pdsrc/*.h)
add_executable(pdsrc ${SOURCES})
target_include_directories(pdsrc PRIVATE ${SFML_INCS})
target_link_libraries(pdsrc sfml-graphics)
