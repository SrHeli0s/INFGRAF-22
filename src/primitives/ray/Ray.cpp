#include "Ray.hpp"
#include "../../point/Point.hpp"
#include "../../vec3/Vec3.hpp"
#include "../sphere/Sphere.hpp"
#include "../plane/Plane.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Ray::Ray() {}

Ray::Ray(Point p, Vec3 v)
{
    this->p = p;
    this->v = v;
}

Intersection intersect(Ray r, Sphere s)
{
    Intersection output;
}

Intersection intersect(Ray r, Plane p)
{
    Intersection output;
}