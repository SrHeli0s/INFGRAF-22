#pragma once
#include <iostream>
#include "../point/Point.hpp"
#include "../vec3/Vec3.hpp"

class Plane;
class Sphere;

class Ray {
    public :
        Point p;
        Vec3 v;

    Ray();
    Ray(Point p, Vec3 v);
};

struct Intersection {
    int value;
    float* positions;
};

Intersection intersect(Ray r, Sphere s);
Intersection intersect(Ray r, Plane p);


std::ostream& operator << (std::ostream& os, const Point& p);

