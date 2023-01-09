#pragma once
#include <cmath>
#include <iostream>
#include "../../vec3/Vec3.hpp"
#include "../../point/Point.hpp"
#include "../../tone_mapping/rgb/Rgb.hpp"
#include "../Primitive.hpp"

class Scene;

class Triangle : public Primitive {
    public:
        float c;
        Point v1, v2, v3;
        Vec3 normal;

        
    Triangle();
    Triangle(Point a, Point b, Point c);
    Triangle(Point a, Point b, Point c, Material material);

    std::vector<Collision> intersect(Ray r) override;
    Point getRandomPoint(Scene sc) override;
};

std::ostream& operator << (std::ostream& os, const Triangle& obj);
