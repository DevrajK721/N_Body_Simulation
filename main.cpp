#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "header.h" // Ensure this contains your Body definition
#include <cstdio>
#include <nlohmann/json.hpp>
#include <cstdlib>


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

// Function to extract data from output file
std::vector<Position> extractData(const std::string& filename, const std::string& targetName)
{
    std::ifstream file(filename);
    std::vector<Position> positions;
    std::string line;

    // Check if file is open
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return positions;
    }

    // Skip the header line
    std::getline(file, line);

    // Read the data
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        double t, x, y, z, vx, vy, vz;

        // Read the data from the line
        time_t time;
        if (iss >> name >> time >> x >> y >> z >> vx >> vy >> vz)
        {
            // Check if name matches targetName
            if (name == targetName)
            {
                // Store x, y, z positions in the array
                positions.push_back({ x, y, z });
            }
        }
    }
    // Close the file
    file.close();
    return positions;
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

    // Store initial positions for plotting
    std::vector<Position> initialPositions(bodies.size());
    for (size_t i = 0; i < bodies.size(); ++i) {
        initialPositions[i] = bodies[i].position; // Store initial position
    }

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

    // Create vectors to hold x, y, and z coordinates for each body
    std::vector<std::vector<double>> xCoordinates(bodies.size());
    std::vector<std::vector<double>> yCoordinates(bodies.size());
    std::vector<std::vector<double>> zCoordinates(bodies.size());

    // Extract data from output file
    for (size_t i = 0; i < bodies.size(); ++i) {
        std::vector<Position> positions = extractData("../output.txt", bodies[i].name);
        for (const auto& position : positions) {
            xCoordinates[i].push_back(position.x); // Store x coordinate
            yCoordinates[i].push_back(position.y); // Store y coordinate
            zCoordinates[i].push_back(position.z); // Store z coordinate
        }
    }

    // Store final positions for plotting
    std::vector<Position> finalPositions(bodies.size());
    for (size_t i = 0; i < bodies.size(); ++i) {
        finalPositions[i] = bodies[i].position; // Store final position
    }

    // Save initial and final positions for Python plotting
    std::ofstream posFile("../positions.txt");
    for (size_t i = 0; i < bodies.size(); ++i) {
        posFile << bodies[i].name << " "
                << initialPositions[i].x << " "
                << initialPositions[i].y << " "
                << initialPositions[i].z << " "
                << finalPositions[i].x << " "
                << finalPositions[i].y << " "
                << finalPositions[i].z << " "
                << bodies[i].mass << std::endl; // Assuming Body has a mass attribute
    }
    posFile.close();

    int result = system("python ../NBodySimViz.py");

    return 0;
}