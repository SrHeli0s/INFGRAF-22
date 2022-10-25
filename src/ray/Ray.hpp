#pragma once
#include <iostream>
#include <vector>
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


std::vector<float> intersect(Ray r, Sphere s);
std::vector<float> intersect(Ray r, Plane p);


std::ostream& operator << (std::ostream& os, const Point& p);

