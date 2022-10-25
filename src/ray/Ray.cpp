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

Intersection intersect(Ray r, Sphere s)
{

    float a = pow(mod(r.v), 2);
    float b = 2.0F*r.v*(r.p - s.center);
    float c = pow(mod(r.p - s.center), 2) - pow(s.radius, 2);

    SecondDegreeEquationSolution intersection = solveSecondDegreeEquation(a,b,c);
    float intersectDistances[intersection.nSols];

    if(intersection.nSols >= 1) intersectDistances[0] = intersection.p1;
    if(intersection.nSols == 2) intersectDistances[1] = intersection.p2;

    Intersection output;

    output = {intersection.nSols, intersectDistances}
}

Intersection intersect(Ray r, Plane p)
{
    Intersection output;
}