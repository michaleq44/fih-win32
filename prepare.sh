#!/usr/bin/env sh

buildcmd="$(command -v make)"
generator="Unix Makefiles"
if command -v ninja 1>&2 2>/dev/null; then
    buildcmd="$(command -v ninja)"
    generator="Ninja"
fi
if [ -z "$buildcmd" ]; then
    echo "Install ninja or make before proceeding"
    exit 1
fi

buildtype=Debug
cmakecmdline=""
for arg in "$@"; do
    if [ "$arg" = "-r" ]; then
        buildtype=Release
    else
        cmakecmdline="$cmakecmdline $arg"
    fi
done

mkdir -p build
CMAKE_CMD="cmake -DCMAKE_BUILD_TYPE=\"$buildtype\" -DCMAKE_MAKE_PROGRAM=\"$buildcmd\" -DCMAKE_TOOLCHAIN_FILE=win32-toolchain.cmake -DCLANG=ON -G \"$generator\" -B build $cmakecmdline"
eval "$CMAKE_CMD"

echo "$buildcmd"