cmake_minimum_required (VERSION 3.5)

project (AntLang)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17")
set (source_dir "${PROJECT_SOURCE_DIR}/src")

file (GLOB_RECURSE source_files "${source_dir}/*.cpp")

add_executable (AntLang ${source_files})
