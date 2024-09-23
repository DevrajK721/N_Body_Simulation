cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/Devra/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(CMAKE_PREFIX_PATH "C:/Users/Devra/vcpkg/installed/x64-windows")

project(N_Body_Simulation)

set(CMAKE_CXX_STANDARD 23)

# Find Python and NumPy
find_package(Python COMPONENTS Development REQUIRED)
execute_process(COMMAND python -c "import numpy; print(numpy.get_include())"
        OUTPUT_VARIABLE NUMPY_INCLUDE_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)

find_path(MATPLOTLIB_CPP_INCLUDE_DIRS "matplotlibcpp.h")
find_package(nlohmann_json CONFIG REQUIRED)

# Create the executable
add_executable(NBodySim main.cpp functions.cpp)

# Include directories for Python, NumPy, and matplotlibcpp
target_include_directories(NBodySim PRIVATE ${MATPLOTLIB_CPP_INCLUDE_DIRS} ${Python_INCLUDE_DIRS} ${NUMPY_INCLUDE_DIR})

# Link Python and NumPy libraries
target_link_libraries(NBodySim PRIVATE nlohmann_json nlohmann_json::nlohmann_json ${Python_LIBRARIES})

# Set the output directory for files
set(OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/output")
file(MAKE_DIRECTORY ${OUTPUT_DIRECTORY})

# Define output file location
add_definitions(-DOUTPUT_DIRECTORY="${OUTPUT_DIRECTORY}/output.txt")

