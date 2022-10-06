#include "Sphere.hpp"
#include "../point/Point.hpp"
#include "../vec3/Vec3.hpp"
#include "../transformation/Transformation.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Sphere::Sphere() {}

Sphere::Sphere(Point center, Vec3 axis, Point reference)
{
    this->center = center;
    this->axis = axis;
    this->reference = reference;
    this->radius = mod(axis)/2;

    if (this->radius - mod(center-reference) < MAX_ERROR) {
        cerr << "The definition of the sphere with center " << center 
        << " axis " << axis << " and reference " << reference 
        << " is inconsistent with the radius of it\n" << endl;
    }
}

Point Sphere::surfacePoint(float inclination, float azimuth) 
{
    Point target = Point(this->radius*sin(inclination)*cos(azimuth),
                 this->radius*sin(inclination)*sin(azimuth),
                 this->radius*cos(inclination)); // Point of sphere with center (0,0,0)

    Vec3 normal = this->reference - this->center;
    Transformation t = BaseChangeTransform(normal, normalize(this->axis), cross(normal,normalize(this->axis)), this->center);
    target.applyTransformation(t);
    return target;
}