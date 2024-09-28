# N-Body Simulation

This project implements an N-body simulation using C++. It utilizes CMake for building the project and supports visualization through Python libraries.

## Prerequisites

- CMake (version 3.10 or higher)
- A C++ compiler that supports C++20
- Python (with NumPy installed, if you plan to use Python for visualization)
- Optional: `matplotlib-cpp` for visualization

## Getting Started

### Step 1: Clone the Repository

First, clone this repository to your local machine:

```bash
git clone https://github.com/DevrajK721/N_Body_Simulation.git
cd N_Body_Simulation
```

### Step 2: Update the CMakeLists.txt
Before building the project, you may need to update the CMakeLists.txt file to point to the correct directories and libraries.

Set the JSON Directory: Locate the line below in CMakeLists.txt:
```
set(JSON_DIR "")
```
Update the JSON_DIR variable to the directory where your JSON library is located. For example:
```
set(JSON_DIR "/path/to/json/include")
```

### Step 3: Build the Project
Once you have made the necessary updates to CMakeLists.txt, you can build the project:

Create a build directory:

```bash
mkdir build
cd build
```
Run CMake to configure the project:

```bash
cmake ..
Build the project:
```
```bash
make
```

### Step 4: Run the Simulation
After building, you can run the simulation with the following command:

```bash
./NBodySim
```
Additional Notes
Ensure that you have all the required dependencies installed for both C++ and Python as mentioned in the prerequisites.
If you plan to visualize the simulation using Python, make sure you have the necessary libraries installed (e.g., matplotlib, numpy).
Troubleshooting
If you encounter errors during the build process, ensure that all paths in the CMakeLists.txt are correctly set.
Check for compatibility issues with your compiler and CMake version.

## Theory

### Newton's Law of Gravitation

Newton's Law of Gravitation describes the gravitational attraction between two bodies. It states that every point mass attracts every other point mass with a force that is directly proportional to the product of their masses and inversely proportional to the square of the distance between their centers. The law is mathematically represented as:

$$\[
F = G \frac{m_1 m_2}{r^2}
\]$$

Where:
- $\( F \)$ is the gravitational force between the two bodies,
- $\( G \)$ is the gravitational constant $(\( G \approx 6.674 \times 10^{-11} \, \textrm{N m}^2/\textrm{kg}^2 \))$,
- $\( m_1 \)$ and $\( m_2 \)$ are the masses of the two bodies,
- $\( r \)$ is the distance between the centers of the two masses.

In our N-body simulation, this principle is applied to compute the gravitational accelerations of each body due to the influence of every other body.

### Runge-Kutta Method

The Runge-Kutta method is a numerical technique used to solve ordinary differential equations (ODEs). In this simulation, we implement the 4th Order Runge-Kutta method (RK4), which provides a good balance between accuracy and computational efficiency. The general form of the RK4 algorithm is given by:

1. **Calculate the derivatives (k-values):**
   - For each time step, calculate the k-values based on the current state of the system:
   $\[
   k_1 = f(t_n, y_n)
   \]
   \[
   k_2 = f\left(t_n + \frac{h}{2}, y_n + \frac{h}{2} k_1\right)
   \]
   \[
   k_3 = f\left(t_n + \frac{h}{2}, y_n + \frac{h}{2} k_2\right)
   \]
   \[
   k_4 = f(t_n + h, y_n + h k_3)
   \]$

2. **Update the state:**
   - The state is then updated using a weighted average of these k-values:
   $\[
   y_{n+1} = y_n + \frac{h}{6}(k_1 + 2k_2 + 2k_3 + k_4)
   \]$

Where:
- $\( t_n \)$ is the current time,
- $\( y_n \)$ is the current state (positions and velocities of the bodies),
- $\( h \)$ is the time step,
- $\( f \)$ is the function representing the system of ODEs.

In the context of the N-body simulation, we calculate the position and velocity of each body at every time step by applying the RK4 method, which utilizes the gravitational forces computed from Newton's law.



