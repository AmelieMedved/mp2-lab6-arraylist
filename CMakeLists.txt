cmake_minimum_required(VERSION 2.8) 

set (CMAKE_CXX_STANDARD 11)
set(PROJECT_NAME mp2-lab6-arraylist)
project(${PROJECT_NAME}) 

set(main main)
set(ArrayList ArrayList)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE) 
if(NOT CMAKE_BUILD_TYPE) 
  set(CMAKE_BUILD_TYPE Release) 
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ArrayList) 

add_subdirectory(gtest) 
add_subdirectory(main)
add_subdirectory(test)
add_subdirectory(ArrayList)
