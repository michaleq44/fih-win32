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

install(TARGETS fih RUNTIME DESTINATION .)
install(FILES LICENSE README.md README.pl.md DESTINATION .)

set(CPACK_PACKAGE_NAME "fih_win32")
set(CPACK_PACKAGE_VENDOR "michaleq44")
set(CPACK_PACKAGE_VERSION "1.0.0")

include(CPack)