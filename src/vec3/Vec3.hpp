#pragma once
#include <iostream>

class Point;
class Transformation;

class Vec3 {
    public:
        float c[3];

    Vec3(float x, float y, float z);
    Vec3();

    const Vec3 operator+ (const Vec3 &v) const;
    const Point operator+ (const Point &p) const;
    const float operator* (const Point &p) const;
    const Vec3 operator- (const Vec3 &v) const;
    const float operator* (const Vec3 &v) const;
    const Vec3 operator*(float t) const;
    const Vec3 operator/(float t) const;

    Vec3 applyTransformation(Transformation t);
};

std::ostream& operator << (std::ostream& os, const Vec3& obj);

Vec3 cross(Vec3 v1, Vec3 v2);

float mod(Vec3 v);

Vec3 inverse(Vec3 v);

Vec3 normalize(Vec3 v);

Vec3 perpendicular(Vec3 v);
