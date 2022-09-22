#include "Vec3.h"
#include "Point.h"
#include <iostream>

using namespace std;

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

ostream& operator << (std::ostream& os, const Point& p)
{
    os << "Point(" << p.c[0] << ", " << p.c[1] << ", " << p.c[2] << ")";
    return os;
}