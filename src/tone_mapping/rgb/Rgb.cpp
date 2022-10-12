#include "Rgb.hpp"
#include <iostream>
#include <cmath>

using namespace std;

RGB::RGB() {}

RGB::RGB(float red, float green, float blue)
{
    this->r = red;
    this->g = green;
    this->b = blue;
}

ostream& operator << (std::ostream& os, const RGB& p)
{
    os << "RGB(" << p.r << ", " << p.g << ", " << p.b << ")";
    return os;
}

std::vector<std::vector<RGB>> clamp(std::vector<std::vector<RGB>> p, float max_value)
{
    for (int i = p.size()-1; i>=0; i--) {
        for(int j = p[i].size(); j>=0; j--) {
            if (p[i][j].r > max_value) p[i][j].r = max_value;
            if (p[i][j].g > max_value) p[i][j].g = max_value;
            if (p[i][j].b > max_value) p[i][j].b = max_value;
        }
    }
    return p;
}