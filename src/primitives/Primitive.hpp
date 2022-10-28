#pragma once

#include "../tone_mapping/rgb/Rgb.hpp"
#include "../ray/Ray.hpp"


class Primitive {
    public:
        RGB emission;

    std::vector<float> intersect(Ray r) {}
    std::string printear() const {}
};

std::ostream& operator << (std::ostream& os, const Primitive& p);
