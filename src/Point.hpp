#pragma once
#include <iostream>

using namespace std;

class Vec3;

class Point {

    public :
        float c[3];

    Point(float x, float y, float z);
    const Vec3 operator- (const Point &p) const;
    const Point operator+ (const Vec3 &v) const;
};

ostream& operator << (std::ostream& os, const Point& p);

