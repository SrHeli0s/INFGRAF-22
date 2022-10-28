#pragma once
#include <iostream>
#include <vector>
#include "../point/Point.hpp"
#include "../vec3/Vec3.hpp"
#include "../primitives/sphere/Sphere.hpp"
#include "../primitives/plane/Plane.hpp"
#include "../tone_mapping/image/Image.hpp"


class Camera {
    public :
        Point o;
        Vec3 u, l, f; //Up, left, foward
        float w,h;  //Size of the image

    Camera();
    Camera(Point o, Vec3 u, Vec3 l, Vec3 f);
    Camera(Point o, Vec3 u, Vec3 l, Vec3 f, float w, float h);

    Image render(std::vector<Sphere> spheres, std::vector<Plane> planes);
};

std::ostream& operator << (std::ostream& os, const Camera& c);