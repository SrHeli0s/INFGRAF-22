#pragma once

#include "../tone_mapping/rgb/Rgb.hpp"
#include "../ray/Ray.hpp"


class Primitive {
    public:
        RGB emission;

    virtual std::vector<float> intersect(Ray r) = 0;
};

