# CMakeList.txt : CMake project for AAL, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("AAL")

# Add source to this project's executable.
add_executable (AAL "main.cpp" "PointGeneration.h" "Voxelization.h"  )

# TODO: Add tests and install targets if needed.
