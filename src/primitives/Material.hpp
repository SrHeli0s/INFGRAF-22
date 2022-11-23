#pragma once
#include "../tone_mapping/rgb/Rgb.hpp"

class Material {
public:
    // kd: diffuse coeficient
    // ks: specular coeficient
    // kt: refraction coeficient
    // ke: emission coeficient
    float kd, ks, kt, ke;
    RGB dif, spec, refr;
    //TODO: Mover emission de primitive a aqui:
    // RGB emission


    Material();
    Material(float kd, float ks, float kt, float ke, RGB diffuse, RGB specular, RGB refraction);
};

