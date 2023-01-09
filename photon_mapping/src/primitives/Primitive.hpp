#pragma once

#include "../tone_mapping/rgb/Rgb.hpp"
#include "../render/ray/Ray.hpp"
#include "Material.hpp"

class Scene;

class Primitive {
    public:
        Material material;

    virtual std::vector<Collision> intersect(Ray r) = 0;
    virtual Point getRandomPoint(Scene sc) = 0;
    virtual RGB getDiffusion(Point p) { return material.dif; }
};