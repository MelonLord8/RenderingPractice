cmake_minimum_required(VERSION 3.10.0)
project(spheres VERSION 1.0.0)

find_package(OpenGL REQUIRED)

add_executable(spheres 
    src/main.h 
    src/main.cpp 
    src/glad.c
    src/Triangle.cpp
    src/Triangle.h
    src/Sphere.h
    src/Sphere.cpp)

target_include_directories(spheres PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/include)
target_link_libraries(spheres PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/lib/libglfw3.a)

set_target_properties(spheres PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)