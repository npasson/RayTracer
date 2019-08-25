cmake_minimum_required(VERSION 3.14)
project(RayTracing)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(math math_files)
aux_source_directory(generic generic_files)
aux_source_directory(objects object_files)

add_executable(RayTracing
        main.cpp
        ${generic_files}
        ${math_files}
        ${object_files}
        Bitmap.cpp
        Bitmap.h)