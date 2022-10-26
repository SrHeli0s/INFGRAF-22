#pragma once
#include <iostream>
#include "../point/Point.hpp"
#include "../vec3/Vec3.hpp"

class Camera {
    public :
        Point o;
        Vec3 u, l, f; //Up, left, foward
        float w,h;  //Size of the image

    Camera();
    Camera(Point o, Vec3 u, Vec3 l, Vec3 f);
    Camera(Point o, Vec3 u, Vec3 l, Vec3 f, float w, float h);
};

std::ostream& operator << (std::ostream& os, const Camera& c);