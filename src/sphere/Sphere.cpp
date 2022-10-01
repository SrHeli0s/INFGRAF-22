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

    if (abs(mod(axis)/2 - mod(center-reference)) < MAX_ERROR) {
        cerr << "The definition of the sphere with center " << center 
        << " axis " << axis << " and reference " << reference 
        << " is inconsistent with the radius of it";
    }
}

Point Sphere::surfacePoint(float inclination, float azimuth) 
{

}