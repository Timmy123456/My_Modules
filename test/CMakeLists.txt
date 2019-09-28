cmake_minimum_required( VERSION 2.8 )
project ( power_line_detector )

set( CMAKE_CXX_COMPILER "g++" )
set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )


############### dependencies ######################


############### source and test ######################
include_directories( ~/Documents/My_Modules )
add_executable( test test.cpp 
)

target_link_libraries( test /home/pi/Documents/My_Modules/libs/c++/libmodules_tcp.a)