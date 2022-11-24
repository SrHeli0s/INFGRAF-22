#include "Plane.hpp"
#include "../../vec3/Vec3.hpp"
#include "../../render/ray/Ray.hpp"
#include "../../tone_mapping/rgb/Rgb.hpp"
#include "../../utils/Utils.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include <memory>

using namespace std;

Plane::Plane() {}

Plane::Plane(float c, Vec3 normal)
{
    this->c = c;
    this->normal = normalize(normal);
    this->emission = RGB(0.2,0.2,0.2);
    this->material = Material(1.0,0,0,0,RGB(0.2,0.2,0.2),RGB(),RGB(),1);
}

Plane::Plane(float c, Vec3 normal, RGB emission) {
    this->c = c;
    this->normal = normalize(normal);
    this->emission = emission;
    this->material = Material(1.0,0,0,0,emission,RGB(),RGB(),1);
}

Plane::Plane(float c, Vec3 normal, RGB emission, Material material)
{
    this->c = c;
    this->normal = normalize(normal);
    this->emission = emission;
    this->material = material;
}

vector<Collision> Plane::intersect(Ray r) {
    vector<Collision> output;
    if(r.v*this->normal == 0) return output;

    float distance = -(this->c + this->normal*r.p)/(r.v*this->normal);
    if(distance<0) return output; //The plane is behind the ray
    
    if (distance>MIN_DISTANCE) output.push_back({make_shared<Plane>(*this),r.p+(r.v*distance),this->normal,r,distance});
    return output;
}

std::ostream& operator << (std::ostream& os, const Plane& obj) {
    os << "Plane(c=" << obj.c << ", normal=" << obj.normal << ", emission=" << obj.emission << ")";

    return os;
}