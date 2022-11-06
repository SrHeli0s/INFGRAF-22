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

ostream& operator << (ostream& os, const RGB& obj)
{
    os << "RGB(" << obj.r << ", " << obj.g << ", " << obj.b << ")";
    return os;
}

vector<vector<RGB>> clamp(vector<vector<RGB>> p, float max_value)
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

const RGB RGB::operator/(float f) const {
    return RGB(this->r/f, this->g/f, this->b/f);
}
const RGB RGB::operator/(RGB f) const {
    return RGB(this->r/f.r, this->g/f.g, this->b/f.b);
}

const RGB RGB::operator+(float f) const {
    return RGB(this->r+f, this->g+f, this->b+f);
}
const RGB RGB::operator+(RGB f) const {
    return RGB(this->r+f.r, this->g+f.g, this->b+f.b);
}

const RGB RGB::operator-(float f) const {
    return RGB(this->r-f, this->g-f, this->b-f);
}
const RGB RGB::operator-(RGB f) const {
    return RGB(this->r-f.r, this->g-f.g, this->b-f.b);
}

const RGB RGB::operator*(float f) const {
    return RGB(this->r*f, this->g*f, this->b*f);
}
const RGB RGB::operator*(RGB f) const {
    return RGB(this->r*f.r, this->g*f.g, this->b*f.b);
}