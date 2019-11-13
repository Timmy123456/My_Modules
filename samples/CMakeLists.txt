cmake_minimum_required( VERSION 2.8 )
project ( power_line_detector )

set( CMAKE_CXX_COMPILER "g++" )
set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )


############### dependencies ######################


############### source and test ######################
include_directories( ~/Documents/My_Modules )
add_executable( tcpserver tcpserver.cpp 
)
target_link_libraries( tcpserver /home/pi/Documents/My_Modules/libs/c++/libmodules.a)

add_executable( tcpclient tcpclient.cpp 
)
target_link_libraries( tcpclient /home/pi/Documents/My_Modules/libs/c++/libmodules.a)

add_executable( serial wiring_serial.cpp 
)
target_link_libraries( serial /home/pi/Documents/My_Modules/libs/c++/libmodules.a wiringPi)