#pragma once

class Material {
    public:
        // kd: diffuse coeficient
        // ks: specular coeficient
        // kt: refraction coeficient
        // ke: emission coeficient
        float kd, ks, kt, ke;

    Material();
    Material(float kd, float ks, float kt, float ke);
};

