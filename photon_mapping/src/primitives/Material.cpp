#include "Material.hpp"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

Material::Material()
{
    this->kd = 0.7;
    this->dif = RGB(0.7,0.7,0.7);
    this->ks = 0;
    this->refr = RGB();
    this->kt = 0;
    this->spec = RGB();
    this->ri = 1;
    this->emission = RGB();
    this->ke = 0;
}
Material::Material(RGB diffuse, RGB specular, RGB refraction, RGB emission, float ri) 
{
    this->dif = diffuse;
    this->spec = specular;
    this->refr = refraction;
    this->emission = emission;
    this->kd = diffuse.maxChannel();
    this->ks = specular.maxChannel();
    this->kt = refraction.maxChannel();
    this->ke = emission.maxChannel();
    this->ri = ri;
}

Material::Material(float kd, float ks, float kt, float ke, RGB diffuse, RGB specular, RGB refraction, RGB emission, float ri)
{
    this->kd = kd;
    this->ks = ks;
    this->kt = kt;
    this->ke = ke;
    this->dif = diffuse;
    this->spec = specular;
    this->refr = refraction;
    this->emission = emission;
    this->ri = ri;

    if ((this->kd + this->ks + this->kt) > 1) {
        std::cerr << "The sum of difusse, specular and refraction coeficients must be less than or equal 1" << std::endl;
    }

    if(this->ke != 0 && this->ks != 0 && this->kt != 0) {
        std::cerr << "Emissive objects do not reflect/refract" << std::endl;
    }
}

ostream& operator << (ostream& os, const Material& obj) {
    os << "Material(diff=" << obj.kd << ":" << obj.dif
       << ", spec=" << obj.ks << ":" << obj.spec
       << ", refr=" << obj.kt << ":" << obj.refr << ":" << obj.ri
       << ", ke=" << obj.ke << ")";
    
    return os;
}

Material LightMat(RGB color)
{
    return Material(RGB(),RGB(),RGB(),color);
}