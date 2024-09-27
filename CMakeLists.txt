# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.16)

# Name of the project
project(N_Body_Simulation)

# Set the C++ standard to use
set(CMAKE_CXX_STANDARD 23)

# Paths to libraries
set(GLFW_DIR "C:/Users/Devra/OneDrive - Imperial College London/Current Work/Quantitative Finance Preparation/C++ Work/Libraries/Libs/glfw")
set(JSON_DIR "C:/Users/Devra/OneDrive - Imperial College London/Current Work/Quantitative Finance Preparation/C++ Work/Libraries/Libs/json")
set(GLEW_DIR "C:/Users/Devra/OneDrive - Imperial College London/Current Work/Quantitative Finance Preparation/C++ Work/Libraries/Libs/glew")
set(GLM_DIR "C:/Users/Devra/OneDrive - Imperial College London/Current Work/Quantitative Finance Preparation/C++ Work/Libraries/Libs/glm")
set(OPENGL_DIR "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64")

# The source files for my project
add_executable(NBodySim main.cpp functions.cpp)
# The "include" directories
#target_include_directories(NBodySim PRIVATE "${GLFW_DIR}/include")
include_directories("${JSON_DIR}/include")
include_directories("${GLEW_DIR}/include")
include_directories("${GLFW_DIR}/include")

# Check if libraries are found
message(STATUS "GLFW_DIR: ${GLFW_DIR}")
message(STATUS "GLEW_DIR: ${GLEW_DIR}")
message(STATUS "OPENGL_DIR: ${OPENGL_LIBRARY}")

set(GLU_LIBRARY "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64/GlU32.Lib")

# Find and link libraries
find_library(GLFW_LIBRARY NAMES glfw3 HINTS "${GLFW_DIR}/src/Release" NO_DEFAULT_PATH)
find_library(GLEW_LIBRARY NAMES glew32 HINTS "${GLEW_DIR}/lib/Release/x64" NO_DEFAULT_PATH)
find_library(OPENGL_LIBRARY NAMES OpenGL32 HINTS "${OPENGL_DIR}" NO_DEFAULT_PATH)
target_link_libraries(NBodySim ${GLEW_LIBRARY} ${GLFW_LIBRARY} ${OPENGL_LIBRARY} ${GLU_LIBRARY})
