cmake_minimum_required(VERSION "3.16")
project(hello)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED 1)

include_directories(fmt/include)
add_subdirectory(fmt)

add_executable(hello hello.cpp)
target_link_libraries(hello PRIVATE fmt::fmt)
