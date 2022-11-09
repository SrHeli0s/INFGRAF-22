#pragma once
#include <cmath>
#include <iostream>
#include "../../vec3/Vec3.hpp"
#include "../../tone_mapping/rgb/Rgb.hpp"
#include "../../tone_mapping/image/Image.hpp"
#include "../Primitive.hpp"


class Sprite : public Primitive {
    private:
        Vec3 a,b;
    public:
        float c;
        Vec3 normal;

        Point center;
        Image img;
        float scale;
        RGB transparent; 
        
    Sprite(Point center, Vec3 normal, Vec3 up, const char* path, float scale);
    Sprite(Point center, Vec3 normal, Vec3 up, const char* path, float scale, RGB transparent_color);

    std::vector<Collision> intersect(Ray r) override;
    RGB getEmission(Point p) override;

    bool insideSprite(Point p);
};

std::ostream& operator << (std::ostream& os, const Sprite& obj);
