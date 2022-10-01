#pragma once
#include <iostream>

using namespace std;

class Vec3;
class Point;

class Transformation {
    public :
        float m[4][4] {};

    Transformation();
    Transformation(float a, float b, float c, float d,
                   float e, float f, float g, float h,
                   float i, float j, float k, float l,
                   float m, float n, float o, float p);

    const Transformation operator* (const Transformation &t) const;

    Transformation inverse();

};

// Constructor helpers
Transformation TranslationTransform(float tx, float ty, float tz);
Transformation ScaleTransform(float sx, float sy, float sz);
Transformation XRotationTransform(float rad);
Transformation YRotationTransform(float rad);
Transformation ZRotationTransform(float rad);
Transformation BaseChangeTransform(Vec3 bx, Vec3 by, Vec3 bz, Point p);

std::ostream& operator << (std::ostream& os, const Transformation& t);

