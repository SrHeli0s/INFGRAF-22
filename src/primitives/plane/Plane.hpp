#pragma once
#include <cmath>
#include <iostream>
#include "../../vec3/Vec3.hpp"
#include "../../tone_mapping/rgb/Rgb.hpp"
#include "../Primitive.hpp"


class Plane : public Primitive {
    public:
        float c;
        Vec3 normal;
        
    Plane();
    Plane(float c, Vec3 normal);
    Plane(float c, Vec3 normal, RGB emission);

    std::vector<float> intersect(Ray r) override;

};

std::ostream& operator << (std::ostream& os, const Plane& p);
