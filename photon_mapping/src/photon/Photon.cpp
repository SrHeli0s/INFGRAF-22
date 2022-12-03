#include "Photon.hpp"
#include "../vec3/Vec3.hpp"
#include "../point/Point.hpp"
#include "../tone_mapping/rgb/Rgb.hpp"
#include "../utils/kdtree.h"
#include <iostream>

using namespace std;

Photon::Photon() {}

Photon::Photon(Point p, RGB flux)
{
    this->p = p;
    this->flux = flux;
}
