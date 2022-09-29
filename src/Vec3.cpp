#include "Vec3.hpp"
#include "Point.hpp"
#include "Transformation.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Vec3::Vec3(float x, float y, float z)
{
    c[0] = x;
    c[1] = y;
    c[2] = z;
}

const Vec3 Vec3::operator+ (const Vec3 &v) const
{
    return Vec3(this->c[0] + v.c[0], this->c[1] + v.c[1], this->c[2] + v.c[2]);
}

const Point Vec3::operator+ (const Point &p) const
{
    return Point(this->c[0] + p.c[0], this->c[1] + p.c[1], this->c[2] + p.c[2]);
}

const Vec3 Vec3::operator- (const Vec3 &v) const
{
    return Vec3(this->c[0] - v.c[0], this->c[1] - v.c[1], this->c[2] - v.c[2]);
}

const float Vec3::operator* (const Vec3 &v) const
{
    return this->c[0] * v.c[0] + this->c[1] * v.c[1] + this->c[2] * v.c[2];
}

const Vec3 Vec3::operator*(float t) const
{
    return Vec3(this->c[0]*t, this->c[1]*t, this->c[2]*t);
}

const Vec3 Vec3::operator/(float t) const
{
    return Vec3(this->c[0]/t, this->c[1]/t, this->c[2]/t);
}

ostream& operator << (std::ostream& os, const Vec3& v)
{
    os << "Vec3(" << v.c[0] << ", " << v.c[1] << ", " << v.c[2] << ")";
    return os;
}

void Vec3::applyTransformation(Transformation t)
{
    c[0] = c[0]*t.m[0][0] + c[1]*t.m[1][0] + c[2]*t.m[2][0] + 0*t.m[3][0];
    c[1] = c[0]*t.m[0][1] + c[1]*t.m[1][1] + c[2]*t.m[2][1] + 0*t.m[3][1];
    c[2] = c[0]*t.m[0][2] + c[1]*t.m[1][2] + c[2]*t.m[2][2] + 0*t.m[3][2];
}

Vec3 cross(Vec3 v1, Vec3 v2)
{
    float x = v1.c[1]*v2.c[2] - v1.c[2]*v2.c[1];
    float y = -(v1.c[0]*v2.c[2] - v1.c[2]*v2.c[0]);
    float z = v1.c[0]*v2.c[1] - v1.c[1]*v2.c[0];
    return Vec3(x,y,z);
}

float mod(Vec3 v) {
    return sqrt(pow(v.c[0],2) + pow(v.c[1],2) + pow(v.c[2],2));
}

Vec3 normalize(Vec3 v) {
    float length = mod(v);
    return Vec3(v.c[0]/length, v.c[1]/length, v.c[2]/length);
}