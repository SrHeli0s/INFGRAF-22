#include "Triangle.hpp"
#include "../../vec3/Vec3.hpp"
#include "../../point/Point.hpp"
#include "../../render/ray/Ray.hpp"
#include "../../tone_mapping/rgb/Rgb.hpp"
#include "../../utils/Utils.hpp"
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

Triangle::Triangle() {}

Triangle::Triangle(Point a, Point b, Point c, RGB emission = RGB(0.2,0.2,0.2))
{
    this->v1 = a;
    this->v2 = b;
    this->v3 = c;
    this->emission = emission;
    Point centroide = Point((a.c[0]+b.c[0]+c.c[0])/3,(a.c[1]+b.c[1]+c.c[1])/3,(a.c[2]+b.c[2]+c.c[2])/3);
    this->normal = normalize(cross(a-b,a-c));
    this->c = this->normal*(Point(0,0,0)-a);
    this->material = Material(1.0,0,0,0);
}

Triangle::Triangle(Point a, Point b, Point c, RGB emission, Material material)
{
    this->v1 = a;
    this->v2 = b;
    this->v3 = c;
    this->emission = emission;
    Point centroide = Point((a.c[0]+b.c[0]+c.c[0])/3,(a.c[1]+b.c[1]+c.c[1])/3,(a.c[2]+b.c[2]+c.c[2])/3);
    this->normal = normalize(cross(a-b,a-c));
    this->c = this->normal*(Point(0,0,0)-a);
    this->material = material;
}

vector<Collision> Triangle::intersect(Ray r) {
    vector<Collision> output;
    if(r.v*this->normal == 0) return output;

    float distance = -(this->c + this->normal*r.p)/(r.v*this->normal);
    if(distance<0) return output; //The plane is behind the ray

    Point P = r.p + r.v*distance; // Intersection point
    //cout << "P = " << P <<endl;

    // Inside-outside test (https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution)
    
    // edge 1
    Vec3 edge1 = v2 - v1;
    Vec3 vp1 = P - v1;
    Vec3 C1 = cross(edge1,vp1);

    // edge 2
    Vec3 edge2 = v3 - v2;
    Vec3 vp2 = P - v2;
    Vec3 C2 = cross(edge2,vp2);

    // edge 3
    Vec3 edge3 = v1 - v3;
    Vec3 vp3 = P - v3;
    Vec3 C3 = cross(edge3,vp3);

    if ((this->normal*C1 > 0) && (this->normal*C2 > 0) && (this->normal*C3 > 0)) {
        // cout << "INTERSECTA " << distance << endl;
        if (distance>MIN_DISTANCE) output.push_back({make_shared<Triangle>(*this),r.p+(r.v*distance),this->normal,r,distance});
    }
    return output;
}

std::ostream& operator << (std::ostream& os, const Triangle& obj) {
    os << "Triangle(c=" << obj.c << ", vertices:" << obj.v1 << " " << obj.v2 << " " << obj.v3 << ", normal=" << obj.normal << ", emission=" << obj.emission << ")";

    return os;
}