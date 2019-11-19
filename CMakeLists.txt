cmake_minimum_required(VERSION 2.8.8)
project(project)

add_library(src "src/main.cpp")
add_subdirectory("traces")

add_executable(main "src/main.cpp")
target_link_libraries(main src)