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
    this->material = Material();
}

Plane::Plane(float c, Vec3 normal, Material material)
{
    this->c = c;
    this->normal = normalize(normal);
    this->material = material;
}

vector<Collision> Plane::intersect(Ray r) {
    vector<Collision> output;
    if(r.v*this->normal == 0) return output;

    float distance = -(this->c + this->normal*r.p)/(r.v*this->normal);
    if(distance<0) return output; //The plane is behind the ray
    
    if (distance>MIN_DISTANCE) output.push_back({
        make_shared<Plane>(*this),
        r.p+(r.v*distance),
        this->normal,
        r,
        distance
    });
    return output;
}

std::ostream& operator << (std::ostream& os, const Plane& obj) {
    os << "Plane(c=" << obj.c << ", normal=" << obj.normal << ", material=" << obj.material << ")";

    return os;
}