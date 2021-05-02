cmake_minimum_required (VERSION 3.1)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

project (AntLang)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-error=unused-variable --std=c++17 -I/usr/include -fno-exceptions -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS")
# Flags that include llvm-11 (wich we dont have in ubuntu )
# set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/lib -lLLVM-11")
set (source_dir "${PROJECT_SOURCE_DIR}/src")

file (GLOB_RECURSE source_files "${source_dir}/*.cpp")

add_executable (AntLang ${source_files})
