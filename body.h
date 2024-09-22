#ifndef BODY_H
#define BODY_H

#include <string>

// Struct to store the properties of a body - inclusive of initial and current positions, velocities, accelerations, and mass
struct Position {
    double x, y, z;
};

struct Velocity {
    double vx, vy, vz;
};

struct Color {
    int r, g, b;
};

struct Body {
    std::string name;
    double mass;
    Position position;
    Velocity velocity;
    Color color;

    double ax, ay, az;
};

#endif //BODY_H
