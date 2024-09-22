#include "body.h"
#include <cmath>
#include <iostream>

void accelerations(body *bodies, int n, double G);

void RK4(body *bodies, int n, double t, double dt, double G);
