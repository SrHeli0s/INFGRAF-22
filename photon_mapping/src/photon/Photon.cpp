#include "Photon.hpp"
#include "../point/Point.hpp"
#include "../tone_mapping/rgb/Rgb.hpp"
#include "../utils/kdtree.h"
#include <iostream>

using namespace std;

Photon::Photon(): p(Point(0,0,0)), flux(RGB(0,0,0)) { }

Photon::Photon(Point p, RGB flux): p(p), flux(flux) { }

std::ostream& operator << (std::ostream& os, const Photon& obj) {
    os << "Photon(p=" << obj.p << ", flux=" << obj.flux << ")";

    return os;
}
