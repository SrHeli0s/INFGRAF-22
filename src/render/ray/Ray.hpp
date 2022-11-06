#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include "../../point/Point.hpp"
#include "../../vec3/Vec3.hpp"

class Plane;
class Sphere;
class Primitive;

const float MIN_DISTANCE = pow(10,-1);

struct Collision {
    std::shared_ptr<Primitive> obj;
    Point collision_point;
    Vec3 collision_normal;
    float distance;
};

class Ray {
    public :
        Point p;
        Vec3 v;

    Ray();
    Ray(Point p, Vec3 v);
};

std::ostream& operator << (std::ostream& os, const Ray& obj);

