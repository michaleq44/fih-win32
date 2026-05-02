#win32-toolchain.cmake
set(CMAKE_SYSTEM_NAME Windows)

set(CMAKE_C_COMPILER clang-cl)
set(CMAKE_CXX_COMPILER clang-cl)
set(CMAKE_LINKER lld-link)

if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    if(NOT DEFINED WIN_SDK_DIR)
        set(WIN_SDK_DIR "$ENV{HOME}/opt/winsdk/sdk")
    endif()
    if (NOT DEFINED WIN_CRT_DIR)
        set(WIN_CRT_DIR "$ENV{HOME}/opt/winsdk/crt")
    endif()

    set(SDK_FLAGS "/winsdkdir \"${WIN_SDK_DIR}\" /vctoolsdir \"${WIN_CRT_DIR}\"")

    set(CMAKE_C_FLAGS "${SDK_FLAGS}" CACHE STRING "")
    set(CMAKE_CXX_FLAGS  "${SDK_FLAGS}" CACHE STRING "")

    set(CMAKE_EXE_LINKER_FLAGS_INIT
            "/libpath:\"${WIN_CRT_DIR}/lib/x86_64\" /libpath:\"${WIN_SDK_DIR}/lib/um/x86_64\" /libpath:\"${WIN_SDK_DIR}/lib/ucrt/x86_64\""
    )
endif()