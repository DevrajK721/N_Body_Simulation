#ifndef HEADER_H
#define HEADER_H
#include "body.h"
#include <vector>
#include <cmath>
#include <iostream>

void accelerations(std::vector<Body>& bodies, int curr_body, int n, double G);

void RK4(std::vector<Body>& bodies, int n, double t, double dt, double G);

#endif