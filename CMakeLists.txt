cmake_minimum_required(VERSION 3.23)

# Set the path to your vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "C:/Users/Devra/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(N_Body_Simulation)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

# Set CMAKE_PREFIX_PATH to help CMake find packages installed by vcpkg
set(CMAKE_PREFIX_PATH "C:/Users/Devra/vcpkg/installed/x64-windows")

# Find required packages
find_package(nlohmann_json REQUIRED)

# Specify the executable to be built
add_executable(NBodySim main.cpp functions.cpp)

# Link the required libraries to the executable
target_link_libraries(NBodySim PRIVATE nlohmann_json::nlohmann_json)




