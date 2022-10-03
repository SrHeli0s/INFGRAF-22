#include "Sphere.hpp"
#include "../point/Point.hpp"
#include "../vec3/Vec3.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Sphere::Sphere() {}

Sphere::Sphere(Point center, Vec3 axis, Point reference)
{
    this->center = center;
    this->axis = axis;
    this->reference = reference;
    this->radius = abs(mod(axis)/2);

    if (this->radius - mod(center-reference) < MAX_ERROR) {
        cerr << "The definition of the sphere with center " << center 
        << " axis " << axis << " and reference " << reference 
        << " is inconsistent with the radius of it\n" << endl;
    }
}

Point Sphere::surfacePoint(float inclination, float azimuth) 
{
    return Point(this->radius*sin(azimuth)*cos(inclination),
                 this->radius*sin(azimuth)*sin(inclination),
                 this->radius*cos(azimuth));
}