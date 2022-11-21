#pragma once

#include "../tone_mapping/rgb/Rgb.hpp"
#include "../render/ray/Ray.hpp"
#include "Material.hpp"

class Primitive {
    public:
        RGB emission;
        Material material;

    virtual std::vector<Collision> intersect(Ray r) = 0;
    virtual RGB getEmission(Point p) { return emission; }
};