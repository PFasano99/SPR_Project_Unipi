cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
set(CMAKE_TOOLCHAIN_FILE "C:/Users/super/Desktop/vcpkg-master/vcpkg-master/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)

set(SOURCES MotionDetection.cpp)
set(./build ${PROJECT_BINARY_DIR}/bin)

add_executable(motionDetection ${SOURCES})

find_package( OpenCV REQUIRED )
	target_include_directories(motionDetection PRIVATE ${OpenCV_INCLUDE_DIRS} )
		target_link_libraries( motionDetection PRIVATE ${OpenCV_LIBS} )