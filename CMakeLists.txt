cmake_minimum_required (VERSION 3.0.0)
project (Forca VERSION 1.0)

include_directories(./include)

add_executable(  
                program
                src/main.cpp
                src/Forca.cpp
)


