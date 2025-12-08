cmake_minimum_required(VERSION 4.0)
project(2025)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG        12.1.0
)

FetchContent_MakeAvailable(fmt)

function(add_console_executable target_name)
    add_executable(${target_name} ${ARGN})
    target_link_libraries(${target_name} PRIVATE fmt::fmt)
endfunction()

add_console_executable(1 1/main.cpp)
add_console_executable(2 2/main.cpp)
add_console_executable(3 3/main.cpp)
add_console_executable(4 4/main.cpp)
add_console_executable(5 5/main.cpp)
add_console_executable(6 6/main.cpp)
add_console_executable(7 7/main.cpp)
add_console_executable(8 8/main.cpp)
