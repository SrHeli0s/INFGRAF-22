#include "Ray.hpp"
#include "../point/Point.hpp"
#include "../vec3/Vec3.hpp"
#include "../primitives/sphere/Sphere.hpp"
#include "../primitives/plane/Plane.hpp"
#include "../utils/Utils.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Ray::Ray() {}

Ray::Ray(Point p, Vec3 v)
{
    this->p = p;
    this->v = v;
}

vector<float> intersect(Ray r, Sphere s)
{

    float a = pow(mod(r.v), 2);
    float b = r.v*(r.p - s.center)*2.0F;
    float c = pow(mod(r.p - s.center), 2) - pow(s.radius, 2);

    return solveSecondDegreeEquation(a,b,c);
}

vector<float> intersect(Ray r, Plane p)
{
    vector<float> output = vector<float>();

    return output;
}