#pragma once
#include <cmath>
#include <iostream>
#include "../../vec3/Vec3.hpp"
#include "../../tone_mapping/rgb/Rgb.hpp"
#include "../Primitive.hpp"

class Scene;

class Plane : public Primitive {
    public:
        float c;
        Vec3 normal;
        
    Plane();
    Plane(float c, Vec3 normal);
    Plane(float c, Vec3 normal, Material material);

    std::vector<Collision> intersect(Ray r) override;
    Point getRandomPoint(Scene sc) override;
};

std::ostream& operator << (std::ostream& os, const Plane& obj);
