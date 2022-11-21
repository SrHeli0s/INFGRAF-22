#include "Material.hpp"

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
}