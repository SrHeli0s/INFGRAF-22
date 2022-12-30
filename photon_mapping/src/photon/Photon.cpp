#include "Photon.hpp"
#include "../point/Point.hpp"
#include "../tone_mapping/rgb/Rgb.hpp"
#include "../utils/kdtree.h"
#include <iostream>

using namespace std;

Photon::Photon() {
    this->p = Point(0,0,0);
    this->flux = RGB(0,0,0);
}

Photon::Photon(Point p, RGB flux)
{
    this->p = p;
    this->flux = flux; //RGB(0,0,0)
}

std::ostream& operator << (std::ostream& os, const Photon& obj) {
    os << "Photon(p=" << obj.p << ", flux=" << obj.flux << ")";

    return os;
}
