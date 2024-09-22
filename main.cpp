#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include "header.h"

using json = nlohmann::json;

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
};

// Function to read JSON data
bool loadData(const std::string& filename, double& G, std::vector<Body>& bodies) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    json j;
    file >> j;

    // Extract gravitational constant
    G = j["gravitational_constant"];

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
    double G;
    std::vector<Body> bodies;

    // Attempt to load data from the JSON file
    if (loadData("C:/Users/Devra/OneDrive - Imperial College London/Current Work/Quantitative Finance Preparation/C++ Work/C++ Basics/N_Body_Simulation/params.json", G, bodies)) {
        std::cout << "Gravitational Constant: " << G << std::endl;

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
    }

    return 0;
}