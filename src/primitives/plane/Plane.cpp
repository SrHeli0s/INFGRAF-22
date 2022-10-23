#include "Plane.hpp"
#include "../../vec3/Vec3.hpp"
#include "../../tone_mapping/rgb/Rgb.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Plane::Plane() {}

Plane::Plane(float d, Vec3 normal)
{
    this->d = d;
    this->normal = normal;
    this->emission = RGB(0,0,0);
}

Plane::Plane(float d, Vec3 normal, RGB emission) {
    this->d = d;
    this->normal = normal;
    this->emission = emission;
}
