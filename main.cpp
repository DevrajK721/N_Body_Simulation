#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <iomanip>
#include "header.h"

using json = nlohmann::json;

// Function to read JSON data
bool loadData(const std::string& filename, double& G, double& dt, double& T, int& n, std::vector<Body>& bodies) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    json j;
    file >> j;

    // Extract gravitational constant
    G = j["gravitational_constant"];

    // Extract time step (dt), total simulation time (T), and number of bodies (n)
    dt = j["dt"];
    T = j["T"];
    n = j["n"];

    // Extract bodies
    for (const auto& item : j["bodies"]) {
        Body body;
        body.name = item["name"];
        body.mass = item["mass"];
        body.position = { item["position"]["x"], item["position"]["y"], item["position"]["z"] };
        body.velocity = { item["velocity"]["vx"], item["velocity"]["vy"], item["velocity"]["vz"] };
        body.color = { item["color"]["r"], item["color"]["g"], item["color"]["b"] };

        bodies.push_back(body);
    }

    return true;
}


int main() {
    double G, dt, T;
    int n;
    std::vector<Body> bodies;

    // Attempt to load data from the JSON file
    if (loadData("C:/Users/Devra/OneDrive - Imperial College London/Current Work/Quantitative Finance Preparation/C++ Work/C++ Basics/N_Body_Simulation/params.json", G, dt, T, n, bodies)) {
        std::cout << "Gravitational Constant: " << G << std::endl;
        std::cout << "Time Step (dt): " << dt << std::endl;
        std::cout << "Total Simulation Time (T): " << T << std::endl;
        std::cout << "Number of Bodies (n): " << n << std::endl;

        // Loop through each body and print its properties
        for (const auto& body : bodies) {
            std::cout << "Name: " << body.name << std::endl;
            std::cout << "Mass: " << body.mass << std::endl;
            std::cout << "Position: (" << body.position.x << ", " << body.position.y << ", " << body.position.z << ")" << std::endl;
            std::cout << "Velocity: (" << body.velocity.vx << ", " << body.velocity.vy << ", " << body.velocity.vz << ")" << std::endl;
            std::cout << "Color: (" << body.color.r << ", " << body.color.g << ", " << body.color.b << ")" << std::endl;
            std::cout << std::endl;
        }
    } else {
        std::cerr << "Failed to load data from params.json." << std::endl;
        return -1;  // Exit if data load fails
    }

    // Simulation start and end time
    double t0 = 0.0, t = t0;
    double t_final = T;

    // txt output file initialization
    std::string filename = "output.txt";
    std::ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file: " << filename << std::endl;
        return -1;
    }

    // Headers for output file
    outputFile << std::setw(20) << "Body" << std::setw(20) << "Time"
               << std::setw(20) << "x" << std::setw(20) << "y"
               << std::setw(20) << "z" << std::setw(20) << "vx"
               << std::setw(20) << "vy" << std::setw(20) << "vz" << std::endl;

    // Run RK4 Function and write to output file
    for (double t = t0 + dt; t <= T + dt / 2; t += dt) {
        RK4(bodies, n, t, dt, G);  // Call RK4 with vector reference
        for (int i = 0; i < n; i++) {
            outputFile << std::setw(20) << bodies[i].name
                       << std::setw(20) << t
                       << std::setw(20) << bodies[i].position.x
                       << std::setw(20) << bodies[i].position.y
                       << std::setw(20) << bodies[i].position.z
                       << std::setw(20) << bodies[i].velocity.vx
                       << std::setw(20) << bodies[i].velocity.vy
                       << std::setw(20) << bodies[i].velocity.vz << std::endl;
        }
    }
    outputFile.close();

    return 0;
}