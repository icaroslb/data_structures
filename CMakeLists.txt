cmake_minimum_required(VERSION 3.10.0)
project(data_structure VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(structures)

add_executable(data_structure main.cpp)

target_link_libraries(data_structure rb_tree)

