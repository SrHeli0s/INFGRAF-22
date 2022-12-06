#include "Photon.hpp"
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

std::ostream& operator << (std::ostream& os, const Photon& obj) {
    os << "Photon(p=" << obj.p << ", flux=" << obj.flux << ")";

    return os;
}
