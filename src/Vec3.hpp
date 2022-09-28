#pragma once
#include <iostream>

using namespace std;

class Point;
class Transformation;

class Vec3 {
    public:
        float c[3];

    Vec3(float x, float y, float z);

    const Vec3 operator+ (const Vec3 &v) const;
    const Point operator+ (const Point &p) const;
    const Vec3 operator- (const Vec3 &v) const;
    const float operator* (const Vec3 &v) const;
    const Vec3 operator*(float t) const;
    const Vec3 operator/(float t) const;

    void applyTransformation(Transformation t);
};

ostream& operator << (std::ostream& os, const Vec3& v);

Vec3 cross(Vec3 v1, Vec3 v2);

float mod(Vec3 v);

Vec3 normalize(Vec3 v);