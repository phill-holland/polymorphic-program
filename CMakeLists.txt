cmake_minimum_required(VERSION 3.18)

project(cplusplus)

set(CMAKE_BUILD_TYPE "Debug")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#include(FetchContent)
#FetchContent_Declare(
#  common
#  GIT_REPOSITORY git@github.com:satya-das/common.git
#)

#FetchContent_MakeAvailable(common)

#include(FetchContent)
#FetchContent_Declare(
#  cppparser
#  GIT_REPOSITORY git@github.com:satya-das/cppparser.git
#)

#FetchContent_MakeAvailable(cppparser)

include_directories("/usr/include")
include_directories("src/include")

file(GLOB SOURCE CONFIGURE_DEPENDS 
"${PROJECT_SOURCE_DIR}/*.cpp"
"${PROJECT_SOURCE_DIR}/src/source/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} "${CMAKE_THREAD_LIBS_INIT}")
