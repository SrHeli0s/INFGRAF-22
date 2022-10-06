#include "Rgb.hpp"
#include <iostream>
#include <cmath>

using namespace std;

RGB::RGB() {}

RGB::RGB(float red, float green, float blue) {
    this->r = red;
    this->g = green;
    this->b = blue;
}

ostream& operator << (std::ostream& os, const RGB& p)
{
    os << "RGB(" << p.r << ", " << p.g << ", " << p.b << ")";
    return os;
}