// Functions for N-Body simulation

#include <header.h>

// Accelerations
void accelerations(body *bodies, int curr_body, int n, double G) {
    bodies[curr_body].ax = 0;
    bodies[curr_body].ay = 0;
    bodies[curr_body].az = 0;

    for (int i = 0; i < n; i++) {
        if (i != curr_body) {
            // Distance between the two bodies in x, y, and z
            double dx = bodies[i].x - bodies[curr_body].x; // Distance between the two bodies in x
            double dy = bodies[i].y - bodies[curr_body].y; // Distance between the two bodies in y
            double dz = bodies[i].z - bodies[curr_body].z; // Distance between the two bodies in z

            // Distance between the two bodies
            double r = sqrt(dx*dx + dy*dy + dz*dz);

            // Update the accelerations of the current body
            bodies[curr_body].ax += G * bodies[i].mass * dx / (r*r*r);
            bodies[curr_body].ay += G * bodies[i].mass * dy / (r*r*r);
            bodies[curr_body].az += G * bodies[i].mass * dz / (r*r*r);
        }
    }
}

// 4th Order Runge-Kutta Implementation
void RK4(body *bodies, int n, double t, double dt, double G) {
    // Initilaze coefficients for 4th Order Runge-Kutta
    long double k1x, k1y, k1z, k1vx, k1vy, k1vz;
    long double k2x, k2y, k2z, k2vx, k2vy, k2vz;
    long double k3x, k3y, k3z, k3vx, k3vy, k3vz;
    long double k4x, k4y, k4z, k4vx, k4vy, k4vz;

    // Cycle through all bodies
    for (int i = 0; i < n; i++) {
        // Save original positions and velocities for intermediatary state computation
        double x_init = bodies[i].x, y_init = bodies[i].y, z_init = bodies[i].z;
        double vx_init = bodies[i].vx, vy_init = bodies[i].vy, vz_init = bodies[i].vz;

        // Compute k1
        accelerations(bodies, i, n, G);
        k1x = dt * bodies[i].vx;
        k1y = dt * bodies[i].vy;
        k1z = dt * bodies[i].vz;
        k1vx = dt * bodies[i].ax;
        k1vy = dt * bodies[i].ay;
        k1vz = dt * bodies[i].az;

        // Compute temporary positions and velocities for k2
        bodies[i].x = x_init + 0.5 * k1x;
        bodies[i].y = y_init + 0.5 * k1y;
        bodies[i].z = z_init + 0.5 * k1z;
        bodies[i].vx = vx_init + 0.5 * k1vx;
        bodies[i].vy = vy_init + 0.5 * k1vy;
        bodies[i].vz = vz_init + 0.5 * k1vz;

        // Compute k2
        accelerations(bodies, i, n, G);
        k2x = dt * bodies[i].vx;
        k2y = dt * bodies[i].vy;
        k2z = dt * bodies[i].vz;
        k2vx = dt * bodies[i].ax;
        k2vy = dt * bodies[i].ay;
        k2vz = dt * bodies[i].az;

        // Compute temporary positions and velocities for k3
        bodies[i].x = x_init + 0.5 * k2x;
        bodies[i].y = y_init + 0.5 * k2y;
        bodies[i].z = z_init + 0.5 * k2z;
        bodies[i].vx = vx_init + 0.5 * k2vx;
        bodies[i].vy = vy_init + 0.5 * k2vy;
        bodies[i].vz = vz_init + 0.5 * k2vz;

        // Compute k3
        accelerations(bodies, i, n, G);
        k3x = dt * bodies[i].vx;
        k3y = dt * bodies[i].vy;
        k3z = dt * bodies[i].vz;
        k3vx = dt * bodies[i].ax;
        k3vy = dt * bodies[i].ay;
        k3vz = dt * bodies[i].az;

        // Compute temporary positions and velocities for k4
        bodies[i].x = x_init + k3x;
        bodies[i].y = y_init + k3y;
        bodies[i].z = z_init + k3z;
        bodies[i].vx = vx_init + k3vx;
        bodies[i].vy = vy_init + k3vy;
        bodies[i].vz = vz_init + k3vz;

        // Compute k4
        accelerations(bodies, i, n, G);
        k4x = dt * bodies[i].vx;
        k4y = dt * bodies[i].vy;
        k4z = dt * bodies[i].vz;
        k4vx = dt * bodies[i].ax;
        k4vy = dt * bodies[i].ay;
        k4vz = dt * bodies[i].az;

        // Update positions and velocities using 4th Order Runge-Kutta
        bodies[i].x = x_init + (k1x + 2*k2x + 2*k3x + k4x) / 6;
        bodies[i].y = y_init + (k1y + 2*k2y + 2*k3y + k4y) / 6;
        bodies[i].z = z_init + (k1z + 2*k2z + 2*k3z + k4z) / 6;
        bodies[i].vx = vx_init + (k1vx + 2*k2vx + 2*k3vx + k4vx) / 6;
        bodies[i].vy = vy_init + (k1vy + 2*k2vy + 2*k3vy + k4vy) / 6;
        bodies[i].vz = vz_init + (k1vz + 2*k2vz + 2*k3vz + k4vz) / 6;
    }
}




