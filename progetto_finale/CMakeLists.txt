cmake_minimum_required(VERSION 3.20)
project(progetto_finale)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

add_executable(main main.cpp)
find_package(Eigen3 REQUIRED)
target_link_libraries(main PRIVATE Eigen3::Eigen)

