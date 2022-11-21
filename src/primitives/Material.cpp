#include "Material.hpp"
#include <iostream>
#include <sstream>

Material::Material()
{
    this->kd = 1.0;
    this->ks = 0;
    this->kt = 0;
    this->ke = 0;
}

Material::Material(float kd, float ks, float kt, float ke)
{
    this->kd = kd;
    this->ks = ks;
    this->kt = kt;
    this->ke = ke;

    if ((this->kd + this->ks + this->kt) > 1) {
        std::cerr << "The sum of difusse, specular and refraction coeficients must be less than or equal 1" << std::endl;
    }

    if(this->ke != 0 && this->ks != 0 && this->kt != 0) {
        std::cerr << "Emissive objects do not reflect/refract" << std::endl;
    }
}