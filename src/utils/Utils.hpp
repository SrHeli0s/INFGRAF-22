#pragma once
#include <vector>
#include <cmath>

const float ZERO_THRESHOLD = pow(10,-6);

std::vector<float> solveSecondDegreeEquation(float a, float b, float c);
bool isfZero(float a);

