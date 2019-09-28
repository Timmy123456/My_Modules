cmake_minimum_required( VERSION 2.8 )
project ( my_modules )

set( CMAKE_CXX_COMPILER "g++" )
set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

#set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin )
set( LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../libs/c++ )

############### dependencies ######################
# OpenCV
#find_package( OpenCV 3.1 REQUIRED )
#include_directories( ${OpenCV_INCLUDE_DIRS} )

#set( THIRD_PARTY_LIBS 
#    ${OpenCV_LIBS}
#)
############### source and test ######################
#include_directories( ${PROJECT_SOURCE_DIR}/include )
#add_subdirectory( src )

############### source and test ######################
add_library( modules_tcp
	tcp.cpp
)

target_link_libraries( myslam
    ${THIRD_PARTY_LIBS}
)