#include "Transformation.hpp"
#include "../vec3/Vec3.hpp"
#include "../point/Point.hpp"
#include <cmath>
#include <iostream>

using namespace std;

Transformation::Transformation() {}

Transformation::Transformation(float _a, float _b, float _c, float _d, 
                               float _e, float _f, float _g, float _h, 
                               float _i, float _j, float _k, float _l,
                               float _m, float _n, float _o, float _p)
{
    m[0][0] = _a;
    m[0][1] = _b;
    m[0][2] = _c;
    m[0][3] = _d;
    m[1][0] = _e;
    m[1][1] = _f;
    m[1][2] = _g;
    m[1][3] = _h;
    m[2][0] = _i;
    m[2][1] = _j;
    m[2][2] = _k;
    m[2][3] = _l;
    m[3][0] = _m;
    m[3][1] = _n;
    m[3][2] = _o;
    m[3][3] = _p;
}

Transformation TranslationTransform(float tx, float ty, float tz)
{
    return Transformation(1,0,0,tx,0,1,0,ty,0,0,1,tz,0,0,0,1);
}
Transformation ScaleTransform(float sx, float sy, float sz)
{
    return Transformation(sx,0,0,0,0,sy,0,0,0,0,sz,0,0,0,0,1);
}
Transformation XRotationTransform(float rad)
{
    return Transformation(1,0,0,0,0,cos(rad),-sin(rad),0,0,sin(rad),cos(rad),0,0,0,0,1);
}
Transformation YRotationTransform(float rad)
{
    return Transformation(cos(rad),0,sin(rad),0,0,1,0,0,-sin(rad),0,cos(rad),0,0,0,0,1);
}
Transformation ZRotationTransform(float rad)
{
    return Transformation(cos(rad),-sin(rad),0,0,sin(rad),cos(rad),0,0,0,0,1,0,0,0,0,1);
}
Transformation BaseChangeTransform(Vec3 bx, Vec3 by, Vec3 bz, Point p)
{
    return Transformation(bx.c[0],by.c[0],bz.c[0],p.c[0],bx.c[1],by.c[1],bz.c[1],p.c[1],bx.c[2],by.c[2],bz.c[2],p.c[2],0,0,0,1);
}

const Transformation Transformation::operator* (const Transformation &t) const
{
    return Transformation(this->m[0][0]*t.m[0][0] + this->m[0][1]+t.m[1][0] + this->m[0][2]+t.m[2][0] + this->m[0][3]+t.m[3][0],
                          this->m[0][0]*t.m[0][1] + this->m[0][1]+t.m[1][1] + this->m[0][2]+t.m[2][1] + this->m[0][3]+t.m[3][1],
                          this->m[0][0]*t.m[0][2] + this->m[0][1]+t.m[1][2] + this->m[0][2]+t.m[2][2] + this->m[0][3]+t.m[3][2],
                          this->m[0][0]*t.m[0][3] + this->m[0][1]+t.m[1][3] + this->m[0][2]+t.m[2][3] + this->m[0][3]+t.m[3][3],
                          this->m[1][0]*t.m[0][0] + this->m[1][1]+t.m[1][0] + this->m[1][2]+t.m[2][0] + this->m[1][3]+t.m[3][0],
                          this->m[1][0]*t.m[0][1] + this->m[1][1]+t.m[1][1] + this->m[1][2]+t.m[2][1] + this->m[1][3]+t.m[3][1],
                          this->m[1][0]*t.m[0][2] + this->m[1][1]+t.m[1][2] + this->m[1][2]+t.m[2][2] + this->m[1][3]+t.m[3][2],
                          this->m[1][0]*t.m[0][3] + this->m[1][1]+t.m[1][3] + this->m[1][2]+t.m[2][3] + this->m[1][3]+t.m[3][3],
                          this->m[2][0]*t.m[0][0] + this->m[2][1]+t.m[1][0] + this->m[2][2]+t.m[2][0] + this->m[2][3]+t.m[3][0],
                          this->m[2][0]*t.m[0][1] + this->m[2][1]+t.m[1][1] + this->m[2][2]+t.m[2][1] + this->m[2][3]+t.m[3][1],
                          this->m[2][0]*t.m[0][2] + this->m[2][1]+t.m[1][2] + this->m[2][2]+t.m[2][2] + this->m[2][3]+t.m[3][2],
                          this->m[2][0]*t.m[0][3] + this->m[2][1]+t.m[1][3] + this->m[2][2]+t.m[2][3] + this->m[2][3]+t.m[3][3],
                          this->m[3][0]*t.m[0][0] + this->m[3][1]+t.m[1][0] + this->m[3][2]+t.m[2][0] + this->m[3][3]+t.m[3][0],
                          this->m[3][0]*t.m[0][1] + this->m[3][1]+t.m[1][1] + this->m[3][2]+t.m[2][1] + this->m[3][3]+t.m[3][1],
                          this->m[3][0]*t.m[0][2] + this->m[3][1]+t.m[1][2] + this->m[3][2]+t.m[2][2] + this->m[3][3]+t.m[3][2],
                          this->m[3][0]*t.m[0][3] + this->m[3][1]+t.m[1][3] + this->m[3][2]+t.m[2][3] + this->m[3][3]+t.m[3][3]);
}

Transformation Transformation::inverse()
{
    float inv[4][4], det;
    int i, j;

    inv[0][0] = this->m[1][1]  * this->m[2][2] * this->m[3][3] - 
                this->m[1][1]  * this->m[2][3] * this->m[3][2] - 
                this->m[2][1]  * this->m[1][2]  * this->m[3][3] + 
                this->m[2][1]  * this->m[1][3]  * this->m[3][2] +
                this->m[3][1] * this->m[1][2]  * this->m[2][3] - 
                this->m[3][1] * this->m[1][3]  * this->m[2][2];

    inv[1][0] = -this->m[1][0]  * this->m[2][2] * this->m[3][3] + 
                this->m[1][0]  * this->m[2][3] * this->m[3][2] + 
                this->m[2][0]  * this->m[1][2]  * this->m[3][3] - 
                this->m[2][0]  * this->m[1][3]  * this->m[3][2] - 
                this->m[3][0] * this->m[1][2]  * this->m[2][3] + 
                this->m[3][0] * this->m[1][3]  * this->m[2][2];

    inv[2][0] = this->m[1][0]  * this->m[2][1] * this->m[3][3] - 
                this->m[1][0]  * this->m[2][3] * this->m[3][1] - 
                this->m[2][0]  * this->m[1][1] * this->m[3][3] + 
                this->m[2][0]  * this->m[1][3] * this->m[3][1] + 
                this->m[3][0] * this->m[1][1] * this->m[2][3] - 
                this->m[3][0] * this->m[1][3] * this->m[2][1];

    inv[3][0] = -this->m[1][0]  * this->m[2][1] * this->m[3][2] + 
                this->m[1][0]  * this->m[2][2] * this->m[3][1] +
                this->m[2][0]  * this->m[1][1] * this->m[3][2] - 
                this->m[2][0]  * this->m[1][2] * this->m[3][1] - 
                this->m[3][0] * this->m[1][1] * this->m[2][2] + 
                this->m[3][0] * this->m[1][2] * this->m[2][1];

    inv[0][1] = -this->m[0][1]  * this->m[2][2] * this->m[3][3] + 
                this->m[0][1]  * this->m[2][3] * this->m[3][2] + 
                this->m[2][1]  * this->m[0][2] * this->m[3][3] - 
                this->m[2][1]  * this->m[0][3] * this->m[3][2] - 
                this->m[3][1] * this->m[0][2] * this->m[2][3] + 
                this->m[3][1] * this->m[0][3] * this->m[2][2];

    inv[1][1] = this->m[0][0]  * this->m[2][2] * this->m[3][3] - 
                this->m[0][0]  * this->m[2][3] * this->m[3][2] - 
                this->m[2][0]  * this->m[0][2] * this->m[3][3] + 
                this->m[2][0]  * this->m[0][3] * this->m[3][2] + 
                this->m[3][0] * this->m[0][2] * this->m[2][3] - 
                this->m[3][0] * this->m[0][3] * this->m[2][2];

    inv[2][1] = -this->m[0][0]  * this->m[2][1] * this->m[3][3] + 
                this->m[0][0]  * this->m[2][3] * this->m[3][1] + 
                this->m[2][0]  * this->m[0][1] * this->m[3][3] - 
                this->m[2][0]  * this->m[0][3] * this->m[3][1] - 
                this->m[3][0] * this->m[0][1] * this->m[2][3] + 
                this->m[3][0] * this->m[0][3] * this->m[2][1];

    inv[3][1] = this->m[0][0]  * this->m[2][1] * this->m[3][2] - 
                this->m[0][0]  * this->m[2][2] * this->m[3][1] - 
                this->m[2][0]  * this->m[0][1] * this->m[3][2] + 
                this->m[2][0]  * this->m[0][2] * this->m[3][1] + 
                this->m[3][0] * this->m[0][1] * this->m[2][2] - 
                this->m[3][0] * this->m[0][2] * this->m[2][1];

    inv[0][2] = this->m[0][1]  * this->m[1][2] * this->m[3][3] - 
                this->m[0][1]  * this->m[1][3] * this->m[3][2] - 
                this->m[1][1]  * this->m[0][2] * this->m[3][3] + 
                this->m[1][1]  * this->m[0][3] * this->m[3][2] + 
                this->m[3][1] * this->m[0][2] * this->m[1][3] - 
                this->m[3][1] * this->m[0][3] * this->m[1][2];

    inv[1][2] = -this->m[0][0]  * this->m[1][2] * this->m[3][3] + 
                this->m[0][0]  * this->m[1][3] * this->m[3][2] + 
                this->m[1][0]  * this->m[0][2] * this->m[3][3] - 
                this->m[1][0]  * this->m[0][3] * this->m[3][2] - 
                this->m[3][0] * this->m[0][2] * this->m[1][3] + 
                this->m[3][0] * this->m[0][3] * this->m[1][2];

    inv[2][2] = this->m[0][0]  * this->m[1][1] * this->m[3][3] - 
                this->m[0][0]  * this->m[1][3] * this->m[3][1] - 
                this->m[1][0]  * this->m[0][1] * this->m[3][3] + 
                this->m[1][0]  * this->m[0][3] * this->m[3][1] + 
                this->m[3][0] * this->m[0][1] * this->m[1][3] - 
                this->m[3][0] * this->m[0][3] * this->m[1][1];

    inv[3][2] = -this->m[0][0]  * this->m[1][1] * this->m[3][2] + 
                this->m[0][0]  * this->m[1][2] * this->m[3][1] + 
                this->m[1][0]  * this->m[0][1] * this->m[3][2] - 
                this->m[1][0]  * this->m[0][2] * this->m[3][1] - 
                this->m[3][0] * this->m[0][1] * this->m[1][2] + 
                this->m[3][0] * this->m[0][2] * this->m[1][1];

    inv[0][3] = -this->m[0][1] * this->m[1][2] * this->m[2][3] + 
                this->m[0][1] * this->m[1][3] * this->m[2][2] + 
                this->m[1][1] * this->m[0][2] * this->m[2][3] - 
                this->m[1][1] * this->m[0][3] * this->m[2][2] - 
                this->m[2][1] * this->m[0][2] * this->m[1][3] + 
                this->m[2][1] * this->m[0][3] * this->m[1][2];

    inv[1][3] = this->m[0][0] * this->m[1][2] * this->m[2][3] - 
                this->m[0][0] * this->m[1][3] * this->m[2][2] - 
                this->m[1][0] * this->m[0][2] * this->m[2][3] + 
                this->m[1][0] * this->m[0][3] * this->m[2][2] + 
                this->m[2][0] * this->m[0][2] * this->m[1][3] - 
                this->m[2][0] * this->m[0][3] * this->m[1][2];

    inv[2][3] = -this->m[0][0] * this->m[1][1] * this->m[2][3] + 
                this->m[0][0] * this->m[1][3] * this->m[2][1] + 
                this->m[1][0] * this->m[0][1] * this->m[2][3] - 
                this->m[1][0] * this->m[0][3] * this->m[2][1] - 
                this->m[2][0] * this->m[0][1] * this->m[1][3] + 
                this->m[2][0] * this->m[0][3] * this->m[1][1];

    inv[3][3] = this->m[0][0] * this->m[1][1] * this->m[2][2] - 
                this->m[0][0] * this->m[1][2] * this->m[2][1] - 
                this->m[1][0] * this->m[0][1] * this->m[2][2] + 
                this->m[1][0] * this->m[0][2] * this->m[2][1] + 
                this->m[2][0] * this->m[0][1] * this->m[1][2] - 
                this->m[2][0] * this->m[0][2] * this->m[1][1];

    det = this->m[0][0] * inv[0][0] + this->m[0][1] * inv[1][0] + this->m[0][2] * inv[2][0] + this->m[0][3] * inv[3][0];

    if (det == 0) {
        cerr << "Transformation " << *this 
        << " cant be inverted. Did anything explode?" << endl;
        return *this;
    }

    det = 1.0 / det;

    return Transformation(inv[0][0]*det, inv[0][1]*det, inv[0][2]*det, inv[0][3]*det,
                          inv[1][0]*det, inv[1][1]*det, inv[1][2]*det, inv[1][3]*det,
                          inv[2][0]*det, inv[2][1]*det, inv[2][2]*det, inv[2][3]*det,
                          inv[3][0]*det, inv[3][1]*det, inv[3][2]*det, inv[3][3]*det);
}

ostream& operator << (std::ostream& os, const Transformation& t)
{
    os << "Transformation([" << t.m[0][0] << "," << t.m[0][1] << "," << t.m[0][2] << "," << t.m[0][3] << "], [" << t.m[1][0] << "," << t.m[1][1] << "," << t.m[1][2] << "," << t.m[1][3] << "], [" << t.m[2][0] << "," << t.m[2][1] << "," << t.m[2][2] << "," << t.m[2][3] << "], [" << t.m[3][0] << "," << t.m[3][1] << "," << t.m[3][2] << "," << t.m[3][3] << "])";
    return os;
}