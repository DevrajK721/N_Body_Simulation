# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.10)

# Name of the project
project(N_Body_Simulation)

# Set the C++ standard to use
set(CMAKE_CXX_STANDARD 20)

# Specify the Python executable
#set(Python_EXECUTABLE "C:/Users/Devra/anaconda3/python.exe")

## Include Python Libraries since we are using matplotlib-cpp
#find_package(Python3 REQUIRED COMPONENTS Development NumPy)

# Set Json directory
set(JSON_DIR "C:/Users/Devra/OneDrive - Imperial College London/Current Work/Quantitative Finance Preparation/C++ Work/Libraries/Libs/json")
#set(MPL_DIR "C:/Users/Devra/OneDrive - Imperial College London/Current Work/Quantitative Finance Preparation/C++ Work/Libraries/Libs/matplotlib-cpp")

# Add the executable (DO NOT CHANGE)
add_executable(NBodySim main.cpp functions.cpp)

## Include the directories (DO NOT CHANGE)
include_directories("${JSON_DIR}/include") #"${Python3_INCLUDE_DIRS}" "${MPL_DIR}" "${Python3_NumPy_INCLUDE_DIRS}")
#
## Link the libraries (DO NOT CHANGE)
#target_link_libraries(NBodySim ${Python3_LIBRARIES} "C:/Users/Devra/anaconda3/libs/python312_d.lib")