#include "Vec3.hpp"
#include "../point/Point.hpp"
#include "../utils/Utils.hpp"
#include "../transformation/Transformation.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Vec3::Vec3() {}

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

const float Vec3::operator* (const Point &p) const
{
    return this->c[0] * p.c[0] + this->c[1] * p.c[1] + this->c[2] * p.c[2];
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

const bool Vec3::operator==(Vec3 v) const
{
    return this->c[0]==v.c[0] && this->c[1]==v.c[1] && this->c[2]==v.c[2];
}

ostream& operator << (std::ostream& os, const Vec3& obj)
{
    os << "Vec3(" << obj.c[0] << ", " << obj.c[1] << ", " << obj.c[2] << ")";
    return os;
}

Vec3 Vec3::applyTransformation(Transformation t)
{
    return Vec3(c[0]*t.m[0][0] + c[1]*t.m[0][1] + c[2]*t.m[0][2] + 0*t.m[0][3],
                c[0]*t.m[1][0] + c[1]*t.m[1][1] + c[2]*t.m[1][2] + 0*t.m[1][3],
                c[0]*t.m[2][0] + c[1]*t.m[2][1] + c[2]*t.m[2][2] + 0*t.m[2][3]);
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

Vec3 inverse(Vec3 v) {
    return Vec3(-v.c[0], -v.c[1], -v.c[2]);
}

//https://math.stackexchange.com/questions/137362/how-to-find-perpendicular-vector-to-another-vector
Vec3 perpendicular(Vec3 v) {
    if (v.c[2] != 0 && -v.c[0] != v.c[1]) {
        return Vec3(v.c[2], v.c[2], - v.c[0]-v.c[1]);
    } else {
        return Vec3(v.c[1]-v.c[2], v.c[0], v.c[0]);
    }
}

float delta(Vec3 a, Vec3 b) {
    return isfZero(mod(cross(a,b))) ? 1 : 0;
}