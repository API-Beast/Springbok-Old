project(Springbok)
cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules/")

include(EnableCPP11Flag)
include(Subtargets)

set(SPRINGBOK_VERSION "0.1")

ENABLE_CPP11()
if(!MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-constexpr-not-const")
endif()

include(SSTest)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/SSTest/)

add_subdirectory(SSTest)
add_subdirectory(Springbok)
add_subdirectory(Examples)

enable_testing()
add_sstest_executable(SpringbokTest) 
target_link_libraries(SpringbokTest SSTest Springbok)