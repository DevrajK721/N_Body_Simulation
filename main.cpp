#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "header.h" // Ensure this contains your Body definition
#include <nlohmann/json.hpp>
#include <matplotlibcpp.h>

namespace plt = matplotlibcpp;
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
    // Load data
    double G, dt, T;
    int n;
    std::vector<Body> bodies;

    if (!loadData("C:/Users/Devra/OneDrive - Imperial College London/Current Work/Quantitative Finance Preparation/C++ Work/C++ Basics/N_Body_Simulation/params.json", G, dt, T, n, bodies)) {
        std::cerr << "Failed to load data from params.json." << std::endl;
        return -1;
    }

    // Write headers to output file
    std::ofstream outputFile("../output.txt");
    outputFile << std::setw(20) << "Body" << std::setw(20) << "Time"
               << std::setw(20) << "x" << std::setw(20) << "y"
               << std::setw(20) << "z" << std::setw(20) << "vx"
               << std::setw(20) << "vy" << std::setw(20) << "vz" << std::endl;

    // Main simulation loop
    double t0 = 0.0, t_final = T;
    for (double t = t0; t <= t_final; t += dt) {
        RK4(bodies, n, t, dt, G); // Call RK4
        // Write current state to output file
        for (const auto& body : bodies) {
            outputFile << std::setw(20) << body.name
                       << std::setw(20) << t
                       << std::setw(20) << body.position.x
                       << std::setw(20) << body.position.y
                       << std::setw(20) << body.position.z
                       << std::setw(20) << body.velocity.vx
                       << std::setw(20) << body.velocity.vy
                       << std::setw(20) << body.velocity.vz << std::endl;
        }
    }

    outputFile.close(); // Close the output file

    int result = system("cd .. && python NBodySimViz.py");

    if (result != 0) {
        std::cerr << "Error running Python script." << std::endl;
    }

    return 0;
}
