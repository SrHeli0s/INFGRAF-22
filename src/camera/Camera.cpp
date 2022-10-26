#include "Camera.hpp"
#include "../point/Point.hpp"
#include "../vec3/Vec3.hpp"
#include "../primitives/sphere/Sphere.hpp"
#include "../primitives/plane/Plane.hpp"
#include "../utils/Utils.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Camera::Camera() {}

Camera::Camera(Point o, Vec3 u, Vec3 l, Vec3 f, float w, float h)
{
    this->o = o;
    this->u = u;
    this->l = l;
    this->f = f;
    this->w = w;
    this->h = h;
}

Camera::Camera(Point o, Vec3 u, Vec3 l, Vec3 f)
{
    this->o = o;
    this->u = u;
    this->l = l;
    this->f = f;
    this->w = 256;
    this->h = 256;
}

ostream& operator << (ostream& os, const Camera& c) {
    os << "Camera(origin=" << c.o << ", up=" << c.u << ", left=" << c.l
    << ", foward=" << c.f << ", wxh=" << c.w << "x" << c.h << ")";
    return os;
}
