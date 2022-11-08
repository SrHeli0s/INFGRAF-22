#pragma once
#include <iostream>
#include <vector>
#include "../../vec3/Vec3.hpp"
#include "../../tone_mapping/rgb/Rgb.hpp"
#include "../Primitive.hpp"

class Triangle;

class STL : public Primitive {
    public:
        std::vector<Triangle> tris;
        
    STL();
    STL(const char* path, Point center, float scale, RGB emission);

    std::vector<Collision> intersect(Ray r) override;

    private:
        std::vector<float> coordsSTL;
        std::vector<float> normalsSTL;
        std::vector<int> trisSTL;
        std::vector<int> solidRangesSTL;
};

std::ostream& operator << (std::ostream& os, const STL& obj);
