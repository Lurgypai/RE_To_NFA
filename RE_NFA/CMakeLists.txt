# CMakeList.txt : CMake project for RE_NFA, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (RE_NFA "RE_NFA.cpp" "State.cpp" "NFA.cpp")

# TODO: Add tests and install targets if needed.
