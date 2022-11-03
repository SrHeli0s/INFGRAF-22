#pragma once
#include "../../../tone_mapping/rgb/Rgb.hpp"
#include "../../../point/Point.hpp"
#include "../../../vec3/Vec3.hpp"

class PLSource {
    public:
        Point center;
        RGB power;

    PLSource();
    PLSource(Point center, RGB power);
};

std::ostream& operator << (std::ostream& os, const PLSource& obj);