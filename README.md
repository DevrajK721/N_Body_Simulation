# N_Body_Simulation
A 4th order Runge-Kutta implementation to compute the behaviour of N gravitational bodies with 3D Visualization.

## Running the script
### If using `.json` for parameters
### 1. `gravitational_constant` (float)
- **Description**: The universal gravitational constant \( G \) used in calculations for Newton's law of gravitation.
- **Units**: \( m^3 \cdot kg^{-1} \cdot s^{-2} \)
- **Example**: `6.67430e-11`

### 2. `bodies` (array of objects)
- **Description**: An array where each object defines a celestial body with several properties.

  #### Each `body` object contains:

  #### `name` (string)
    - **Description**: A unique identifier for the celestial body.
    - **Example**: `"Body1"`

  #### `mass` (float)
    - **Description**: The mass of the body in kilograms.
    - **Units**: Kilograms (kg)
    - **Example**: `5.972e24` (Earth's mass)

  #### `position` (object)
    - **Description**: The initial position of the body in 3D space, represented by `x`, `y`, and `z` coordinates.
    - **Units**: Meters (m)
    - **Example**:
      ```json
      {
        "x": 0.0,
        "y": 0.0,
        "z": 0.0
      }
      ```

  #### `velocity` (object)
    - **Description**: The initial velocity of the body in 3D space, represented by `vx`, `vy`, and `vz` components.
    - **Units**: Meters per second (m/s)
    - **Example**:
      ```json
      {
        "vx": 0.0,
        "vy": 1022.0,
        "vz": 0.0
      }
      ```

  #### `color` (object)
    - **Description**: The color of the body for 3D rendering, represented in RGB format.
    - **Values**: Each component `r`, `g`, and `b` is an integer between `0` and `255`.
    - **Example**:
      ```json
      {
        "r": 255,
        "g": 255,
        "b": 0
      }
      ```

### Example JSON Body Object
Here's a complete example of a body object for Earth:
```json
{
  "name": "Earth",
  "mass": 5.972e24,
  "position": {
    "x": 0.0,
    "y": 0.0,
    "z": 0.0
  },
  "velocity": {
    "vx": 0.0,
    "vy": 0.0,
    "vz": 0.0
  },
  "color": {
    "r": 0,
    "g": 0,
    "b": 255
  }
}
## Theory



