cmake_minimum_required(VERSION 3.20)
project(esercitazione5)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")
enable_testing()
set(SRC_test_sorts timecounter.cpp main.cpp)
add_executable(main ${SRC_test_sorts})

add_executable(test_merge_sort test_merge_sort.cpp)
add_test(NAME mergesort COMMAND test_merge_sort)

add_executable(test_quicksort test_quicksort.cpp)
add_test(NAME quicksort COMMAND test_quicksort)

