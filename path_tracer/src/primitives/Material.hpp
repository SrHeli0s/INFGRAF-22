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
    RGB dif, spec, refr;
    //TODO: Mover emission de primitive a aqui:
    // RGB emission


    Material();
    Material(RGB diffuse, RGB specular, RGB refraction, float ri);
    Material(float kd, float ks, float kt, float ke, RGB diffuse, RGB specular, RGB refraction, float ri);
};

std::ostream& operator << (std::ostream& os, const Material& obj);

