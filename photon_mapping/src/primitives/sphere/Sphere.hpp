#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include "../../point/Point.hpp"
#include "../../vec3/Vec3.hpp"
#include "../../tone_mapping/rgb/Rgb.hpp"
#include "../Primitive.hpp"

const float MAX_ERROR = pow(10,-6);

class Scene;

class Sphere : public Primitive{
    public:
        Point center;
        Vec3 axis;
        Point reference;
        float radius;
        
    Sphere();
    Sphere(Point center, Vec3 axis, Point reference);
    Sphere(Point center, Vec3 axis, Point reference, Material material);

    Point surfacePoint(float inclination, float azimuth);

    std::vector<Collision> intersect(Ray r) override;
    Point getRandomPoint(Scene sc) override;
};

std::ostream& operator << (std::ostream& os, const Sphere& obj);
