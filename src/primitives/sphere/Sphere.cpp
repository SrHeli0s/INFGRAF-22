#include "Sphere.hpp"
#include "../../point/Point.hpp"
#include "../../vec3/Vec3.hpp"
#include "../../ray/Ray.hpp"
#include "../../utils/Utils.hpp"
#include "../../transformation/Transformation.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;

Sphere::Sphere() {}

Sphere::Sphere(Point center, Vec3 axis, Point reference)
{
    this->emission = RGB(200,200,200);
    this->center = center;
    this->axis = axis;
    this->reference = reference;
    this->radius = mod(axis)/2;

    if (this->radius - mod(center-reference) > MAX_ERROR) {
        cerr << "The definition of the sphere with center " << center 
        << " axis " << axis << " and reference " << reference 
        << " is inconsistent with the radius of it\n" << endl;
    }
}

Sphere::Sphere(Point center, Vec3 axis, Point reference, RGB emission)
{
    this->emission = emission;
    this->center = center;
    this->axis = axis;
    this->reference = reference;
    this->radius = mod(axis)/2;

    if (this->radius - mod(center-reference) > MAX_ERROR) {
        cerr << "The definition of the sphere with center " << center 
        << " axis " << axis << " and reference " << reference 
        << " is inconsistent with the radius of it\n" << endl;
    }
}


Point Sphere::surfacePoint(float inclination, float azimuth) 
{
    Point target = Point(sin(inclination)*cos(azimuth),
                 sin(inclination)*sin(azimuth),
                 cos(inclination)); // Point of sphere with center (0,0,0)

    Vec3 normal = this->reference - this->center;
    Transformation t = BaseChangeTransform(normal, normalize(this->axis), cross(normal,normalize(this->axis)), this->center);
    
    cout << "\n"<< "\nVoy a aplicar la transformacion " << t << " al punto " << target<< "\n"<< "\n";
    // cout << "\n" << t << "\n" << target<< "\n"<< "\n";
    return target.applyTransformation(t);;
}

vector<float> Sphere::intersect(Ray r) {
    float a = pow(mod(r.v), 2);
    float b = r.v*(r.p - this->center)*2.0F;
    float c = pow(mod(r.p - this->center), 2) - pow(this->radius, 2);

    return solveSecondDegreeEquation(a,b,c);
}

string Sphere::printear() const {
    stringstream ss;
    ss << "Sphere(center=" << this->center << ", axis=" << this->axis << ")";
    return ss.str();
}