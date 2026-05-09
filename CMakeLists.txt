cmake_minimum_required(VERSION 3.15)
project(fih_win32 C CXX)

set(CMAKE_C_STANDARD 11)

set(RC_INPUT "${CMAKE_CURRENT_SOURCE_DIR}/src/fih.rc")
set(RC_PREPROCESSED "${CMAKE_CURRENT_BINARY_DIR}/fih.i")
set(RC_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/fih.res")

add_custom_command(
        OUTPUT ${RC_OUTPUT}
        COMMAND ${CMAKE_C_COMPILER} /winsdkdir "${WIN_SDK_DIR}" /vctoolsdir "${WIN_CRT_DIR}" /TC /P ${RC_INPUT} /Fi${RC_PREPROCESSED}
        COMMAND ${CMAKE_RC_COMPILER} /no-preprocess /C 65001 /fo ${RC_OUTPUT} ${RC_PREPROCESSED}
        DEPENDS ${RC_INPUT} ${CMAKE_CURRENT_SOURCE_DIR}/src/fih.ico
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src"
        COMMENT "Preprocess and compile resource file"
        VERBATIM
)

if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    set(RESOURCES ${RC_OUTPUT})
else()
    set(RESOURCES src/fih.rc)
endif()

include_directories(inc/)
add_executable(fih WIN32 src/main.c
        inc/main.h
        src/util.c
        inc/util.h
        src/graphics.cpp
        inc/graphics.h
        ${RESOURCES})
target_link_libraries(fih PRIVATE gdiplus gdi32 user32)
target_compile_definitions(fih PRIVATE UNICODE _UNICODE)
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    set_target_properties(fih PROPERTIES LINK_FLAGS "${RC_OUTPUT}")
endif()

install(TARGETS fih RUNTIME DESTINATION .)
install(FILES LICENSE README.md README.pl.md DESTINATION .)

set(CPACK_PACKAGE_NAME "fih_win32")
set(CPACK_PACKAGE_VENDOR "michaleq44")
set(CPACK_PACKAGE_VERSION "1.2.0")

include(CPack)