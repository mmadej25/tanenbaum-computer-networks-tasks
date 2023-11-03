cmake_minimum_required(VERSION 3.10)
project(CPPUTESTS)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES AllTests.cpp TestChapter2.cpp ../Chapter2.cpp)
add_executable(ut ${SOURCES} )
target_link_libraries(ut PRIVATE -lCppUTest -lCppUTestExt)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")