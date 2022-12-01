#include "Ray.hpp"
#include "../../point/Point.hpp"
#include "../../vec3/Vec3.hpp"
#include "../../primitives/sphere/Sphere.hpp"
#include "../../primitives/plane/Plane.hpp"
#include "../../utils/Utils.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Ray::Ray() {}

Ray::Ray(Point p, Vec3 v)
{
    this->p = p;
    this->v = normalize(v);
}

ostream& operator << (ostream& os, const Ray& obj) {
    os << "Ray(origin=" << obj.p << ", vector=" << obj.v << ")";
    return os;
}
