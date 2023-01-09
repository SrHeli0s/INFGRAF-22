#pragma once
#include <iostream>
#include <vector>
#include "../../vec3/Vec3.hpp"
#include "../../tone_mapping/rgb/Rgb.hpp"
#include "../Primitive.hpp"

class Triangle;
class Scene;

class STL : public Primitive {
    public:
        std::vector<Triangle> tris;
        Point center;
    
        
    STL();
    STL(const char* path, Point center, float scale, Material material);

    std::vector<Collision> intersect(Ray r) override;
    Point getRandomPoint(Scene sc) override;

    private:
        std::vector<float> coordsSTL;
        std::vector<float> normalsSTL;
        std::vector<int> trisSTL;
        std::vector<int> solidRangesSTL;
};

std::ostream& operator << (std::ostream& os, const STL& obj);
