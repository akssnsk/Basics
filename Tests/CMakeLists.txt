cmake_minimum_required(VERSION 2.6)

SET(CMAKE_CXX_FLAGS "-std=gnu++11 -g -ggdb") #Turn on C++11 Support

set(TASKS_TO_TEST Tasks.cpp CutTheTree.cpp Bytes.cpp)
set(CPP_TO_TEST Cpp.cpp)
set(UNIT_TESTS tasks_test.cpp cpp_test.cpp)
set(SRC_DIR ..)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(.)

include_directories(${SRC_DIR}/Tasks)
add_library(tasksToTest ${SRC_DIR}/Tasks/Tasks.cpp ${SRC_DIR}/Tasks/CutTheTree.cpp ${SRC_DIR}/Tasks/Bytes.cpp)
#add_library(tasksToTest ${SRC_DIR}/Tasks/${TASKS_TO_TEST})

include_directories(${SRC_DIR}/Cpp)
add_library(cppToTest ${SRC_DIR}/Cpp/${CPP_TO_TEST})

add_executable(runTests ${UNIT_TESTS})
target_link_libraries(runTests gtest gtest_main rt pthread tasksToTest cppToTest)

