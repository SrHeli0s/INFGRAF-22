#include "Plane.hpp"
#include "../../vec3/Vec3.hpp"
#include "../../ray/Ray.hpp"
#include "../../tone_mapping/rgb/Rgb.hpp"
#include "../../utils/Utils.hpp"
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

Plane::Plane() {}

Plane::Plane(float c, Vec3 normal)
{
    this->c = c;
    this->normal = normal;
    this->emission = RGB(200,200,200);
}

Plane::Plane(float c, Vec3 normal, RGB emission) {
    this->c = c;
    this->normal = normal;
    this->emission = emission;
}

vector<float> Plane::intersect(Ray r) {
    vector<float> output;
    if(r.v*this->normal == 0) return output;

    float distance = (this->c + this->normal*r.p)/(r.v*this->normal);
    if(distance<0) return output; //The plane is behind the ray
    
    output.push_back(distance);
    return output;
}

std::ostream& operator << (std::ostream& os, const Plane& p) {
    os << "Plane(c=" << p.c << ", normal=" << p.normal << ")";

    return os;
}

string Plane::to_string() const {
    stringstream ss;
    ss << "Plane(c=" << this->c << ", normal=" << this->normal << ")";
    return ss.str();
}