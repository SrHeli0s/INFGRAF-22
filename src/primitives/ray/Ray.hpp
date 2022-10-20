#pragma once
#include <iostream>
#include "../../point/Point.hpp"
#include "../../vec3/Vec3.hpp"

class Plane;
class Sphere;

class Ray {
    public :
        Point p;
        Vec3 v;

    Ray();
    Ray(Point p, Vec3 v);
};

struct Collision {
    int value;
    Point* positions;
};

Collision intersect(Ray r, Sphere s);
Collision intersect(Ray r, Plane p);


std::ostream& operator << (std::ostream& os, const Point& p);

