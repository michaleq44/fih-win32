cmake_minimum_required(VERSION 3.15)
project(fih_win32 C CXX)

set(CMAKE_C_STANDARD 11)

include_directories(inc/)
add_executable(fih WIN32 src/main.c
        inc/main.h
        src/util.c
        inc/util.h
        src/graphics.cpp
        inc/graphics.h)
target_link_libraries(fih PRIVATE gdiplus gdi32 user32)
target_compile_definitions(fih PRIVATE UNICODE _UNICODE)