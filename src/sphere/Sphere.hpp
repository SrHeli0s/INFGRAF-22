#pragma once
#include <cmath>
#include <iostream>
#include "../point/Point.hpp"
#include "../vec3/Vec3.hpp"

const float MAX_ERROR = pow(10,-6);

class Sphere {
    public:
        Point center;
        Vec3 axis;
        Point reference;
        float radius;
        
    Sphere();
    Sphere(Point center, Vec3 axis, Point reference);

    Point surfacePoint(float inclination, float azimuth);
};