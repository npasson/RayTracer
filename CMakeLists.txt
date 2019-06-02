cmake_minimum_required(VERSION 3.14)
project(RayTracing)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(math math_files)

add_executable(RayTracing
        main.cpp
        ${math_files}
        generic/defines.h math/Ray3.cpp math/Ray3.h objects/LightSource.cpp objects/LightSource.h math/Color.cpp math/Color.h math/misc.h math/Point.cpp math/Point.h Bitmap.cpp Bitmap.h objects/Camera.cpp objects/Camera.h objects/Plane.cpp objects/Plane.h math/Matrix.cpp math/Matrix.h objects/Solid.cpp objects/Solid.h generic/Debug.cpp generic/Debug.h)