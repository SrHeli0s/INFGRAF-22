#pragma once
#include "../../../tone_mapping/rgb/Rgb.hpp"
#include "../../../point/Point.hpp"
#include "../../../vec3/Vec3.hpp"

class PointLight {
    public:
        Point center;
        RGB power;

    PointLight();
    PointLight(Point center, RGB power);
};

std::ostream& operator << (std::ostream& os, const PointLight& obj);