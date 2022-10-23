#pragma once
#include <cmath>
#include <iostream>
#include "../../point/Point.hpp"
#include "../../vec3/Vec3.hpp"
#include "../../tone_mapping/rgb/Rgb.hpp"

const float MAX_ERROR = pow(10,-6);

class Sphere {
    public:
        Point center;
        Vec3 axis;
        Point reference;
        float radius;
        RGB emission;
        
    Sphere();
    Sphere(Point center, Vec3 axis, Point reference);
    Sphere(Point center, Vec3 axis, Point reference, RGB emission);

    Point surfacePoint(float inclination, float azimuth);
};