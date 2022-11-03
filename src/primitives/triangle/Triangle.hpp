#pragma once
#include <cmath>
#include <iostream>
#include "../../vec3/Vec3.hpp"
#include "../../point/Point.hpp"
#include "../../tone_mapping/rgb/Rgb.hpp"
#include "../Primitive.hpp"


class Triangle : public Primitive {
    public:
        float c;
        Point v1, v2, v3;
        Vec3 normal;

        
    Triangle();
    Triangle(float c, Point v1, Point v2, Point v3, Vec3 normal);
    Triangle(float c, Point v1, Point v2, Point v3, Vec3 normal, RGB emission);

    std::vector<Collision> intersect(Ray r) override;

};

std::ostream& operator << (std::ostream& os, const Triangle& obj);
