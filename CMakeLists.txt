cmake_minimum_required(VERSION 3.5)
project(simplex_volume)

add_library(simplex INTERFACE)
target_include_directories(simplex INTERFACE ${CMAKE_SOURCE_DIR}/src/)

add_executable(app main.cpp)
target_compile_features(app PRIVATE cxx_auto_type cxx_range_for)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

target_link_libraries(app simplex Eigen3::Eigen)
#target_link_libraries(app sqlite3)
