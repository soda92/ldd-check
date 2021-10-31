project(hello)
cmake_minimum_required(VERSION 3.20)

find_package(fmt CONFIG REQUIRED)

add_executable(hello hello.cpp)
target_link_libraries(hello PRIVATE fmt::fmt)
