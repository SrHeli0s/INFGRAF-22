#pragma once
#include <cmath>
#include <iostream>
#include "../../vec3/Vec3.hpp"
#include "../../tone_mapping/rgb/Rgb.hpp"


class Plane {
    public:
        float c;
        Vec3 normal;
        RGB emission;
        
    Plane();
    Plane(float c, Vec3 normal);
    Plane(float c, Vec3 normal, RGB emission);

};