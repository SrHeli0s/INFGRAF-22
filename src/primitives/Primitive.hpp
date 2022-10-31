#pragma once

#include "../tone_mapping/rgb/Rgb.hpp"
#include "../ray/Ray.hpp"


class Primitive {
    public:
        RGB emission;

    virtual std::vector<float> intersect(Ray r) = 0;
    virtual std::string to_string() const = 0;
};

std::ostream& operator << (std::ostream& os, const Primitive& p);
