#include "PLSource.hpp"
#include "../../../tone_mapping/rgb/Rgb.hpp"
#include "../../../point/Point.hpp"
#include "../../../vec3/Vec3.hpp"

using namespace std;

PLSource::PLSource() {}

PLSource::PLSource(Point center, RGB power) {
    this->center = center;
    this->power = power;
}