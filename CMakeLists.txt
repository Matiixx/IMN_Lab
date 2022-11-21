cmake_minimum_required(VERSION 3.1.0)
project(imn)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

# set(INCLUDES ${PROJECT_SOURCE_DIR}/include)
# set(INCLUDES_UTILS ../utils/include)
# include_directories(${INCLUDES})
# include_directories(${INCLUDES_UTILS})

include_directories(utils/include)
include_directories(Lab5/include)

file(GLOB UTILS_SOURCES "utils/src/*.cpp")
file(GLOB UTILS_SOURCES_HEADERS "utils/include/*.h")

set(SOURCES ${UTILS_SOURCES_HEADERS} ${UTILS_SOURCES} Lab5/src/main.cpp)

message(STATUS "FILES: ${SOURCES}")

add_executable(${PROJECT_NAME} ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)