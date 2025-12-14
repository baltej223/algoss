#ifndef   BISECTION_H
#define BISECTION_H

#include <math.h>
#include <stdio.h>
#include <float.h>

float Bisection(float (*eq)(float x), float left, float right, float tol);

#endif
