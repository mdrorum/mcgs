cmake_minimum_required (VERSION 2.6)

project (botclient)

find_package(Boost 1.40.0 REQUIRED COMPONENTS system thread serialization)
include_directories(${Boost_INCLUDE_DIR})

add_definitions(-std=c++11)

include_directories(bots)

link_directories( ${link_directories} ./bots ) 

add_executable(main main.cpp)

# Enlaza el main con la libreria bots
target_link_libraries(main bots)
target_link_libraries(main ${Boost_LIBRARIES})
target_link_libraries(main pthread)

