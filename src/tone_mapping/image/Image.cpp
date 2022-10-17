#include "Image.hpp"
#include <iostream>
#include <fstream>

using namespace std;

Image::Image() {}

Image::Image(vector<vector<RGB>> pixels, float max_value, float color_res)
{
    this->max_value = max_value;
    this->color_res = color_res;
    this->p = pixels;
    this->h = p[0].size();
    this->w = p.size();
}

Image clamp(Image img, float max_clamp)
{
    for (int i = img.w-1; i>=0; i--) {
        for(int j = img.h-1; j>=0; j--) {
            img.p[i][j].r = (img.p[i][j].r > max_clamp) ? max_clamp : img.p[i][j].r;
            img.p[i][j].g = (img.p[i][j].g > max_clamp) ? max_clamp : img.p[i][j].g;
            img.p[i][j].b = (img.p[i][j].b > max_clamp) ? max_clamp : img.p[i][j].b;
        }
    }
    return img;
}

Image equalize(Image img, float max_equalize)
{
    for (int i = img.w-1; i>=0; i--) {
        for(int j = img.h-1; j>=0; j--) {
            img.p[i][j].r = (img.p[i][j].r / img.max_value) * max_equalize;
            img.p[i][j].g = (img.p[i][j].g / img.max_value) * max_equalize;
            img.p[i][j].b = (img.p[i][j].b / img.max_value) * max_equalize;
        }
    }
    return img;
}

ostream& operator << (ostream& os, const Image& p) {
    os << "Image with hxw:" << to_string(p.h)+"x"+to_string(p.w) 
       << " max_value:" << p.max_value 
       << " color_res:" << p.color_res 
       << " pixels:\n";
    for(int i = 0; i<p.w; i++) {
        for(int j = 0; j<p.h; j++) {
            os << p.p[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}
