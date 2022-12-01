#pragma once
#include <vector>
#include <cmath>
#include "../render/ray/Ray.hpp"
#include "../render/scene/Scene.hpp"


const float ZERO_THRESHOLD = pow(10,-6);

std::vector<float> solveSecondDegreeEquation(float a, float b, float c);
bool isfZero(float a);
Collision closest_col(Ray r, Scene s);

