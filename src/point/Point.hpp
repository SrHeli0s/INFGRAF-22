#pragma once
#include <iostream>

class Vec3;
class Transformation;

class Point {
    public :
        float c[3];

    Point();
    Point(float x, float y, float z);
    
    const Vec3 operator- (const Point &p) const;
    const Point operator+ (const Vec3 &v) const;

    Point applyTransformation(Transformation t);
};

std::ostream& operator << (std::ostream& os, const Point& obj);

