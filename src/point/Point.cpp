#include "Point.hpp"
#include "../vec3/Vec3.hpp"
#include "../transformation/Transformation.hpp"
#include <iostream>

using namespace std;

Point::Point() {}

Point::Point(float x, float y, float z)
{
    c[0] = x;
    c[1] = y;
    c[2] = z;
}

const Vec3 Point::operator- (const Point &p) const
{
    return Vec3(this->c[0] - p.c[0], this->c[1] - p.c[1], this->c[2] - p.c[2]);
}

const Point Point::operator+ (const Vec3 &v) const
{
    return Point(this->c[0]+v.c[0], this->c[1]+v.c[1], this->c[2]+v.c[2]);
}

void Point::applyTransformation(Transformation t)
{
    c[0] = c[0]*t.m[0][0] + c[1]*t.m[1][0] + c[2]*t.m[2][0] + 1*t.m[3][0];
    c[1] = c[0]*t.m[0][1] + c[1]*t.m[1][1] + c[2]*t.m[2][1] + 1*t.m[3][1];
    c[2] = c[0]*t.m[0][2] + c[1]*t.m[1][2] + c[2]*t.m[2][2] + 1*t.m[3][2];
}

ostream& operator << (std::ostream& os, const Point& p)
{
    os << "Point(" << p.c[0] << ", " << p.c[1] << ", " << p.c[2] << ")";
    return os;
}