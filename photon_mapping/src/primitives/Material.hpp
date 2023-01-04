#pragma once
#include "../tone_mapping/rgb/Rgb.hpp"

class Material {
public:
    // kd: diffuse coeficient
    // ks: specular coeficient
    // kt: refraction coeficient
    // ke: emission coeficient
    // ri: refraction index
    float kd, ks, kt, ke, ri;
    RGB dif, spec, refr, emission;


    Material();
    Material(RGB diffuse, RGB specular, RGB refraction, RGB emission = RGB(), float ri=1);
    Material(float kd, float ks, float kt, float ke, RGB diffuse, RGB specular, RGB refraction, RGB emission = RGB(), float ri = 1);
};

std::ostream& operator << (std::ostream& os, const Material& obj);

// Constructor helpers
Material LightMat(RGB color);

