#include "PointLight.hpp"
#include "../../../tone_mapping/rgb/Rgb.hpp"
#include "../../../point/Point.hpp"
#include "../../../vec3/Vec3.hpp"

using namespace std;

PointLight::PointLight() {}

PointLight::PointLight(Point center, RGB power) {
    this->center = center;
    this->power = power;
}