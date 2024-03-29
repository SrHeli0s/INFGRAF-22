#include "Image.hpp"
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <fstream>
#include <cmath>

using namespace std;

Image::Image() {}

Image::Image(vector<vector<RGB>> pixels, float max_value, float color_res)
{
    this->max_value = max_value;
    this->color_res = color_res;
    this->p = pixels;
    this->h = p.size();
    this->w = p[0].size();
}

Image clamp(Image img, float max_clamp)
{
    for (int i = img.h-1; i>=0; i--) {
        for(int j = img.w-1; j>=0; j--) {
            img.p[i][j].r = (img.p[i][j].r > max_clamp) ? max_clamp : img.p[i][j].r;
            img.p[i][j].g = (img.p[i][j].g > max_clamp) ? max_clamp : img.p[i][j].g;
            img.p[i][j].b = (img.p[i][j].b > max_clamp) ? max_clamp : img.p[i][j].b;
        }
    }
    img.max_value = max_clamp;
    return img;
}

Image equalize(Image img)
{
    for (int i = img.h-1; i>=0; i--) {
        for(int j = img.w-1; j>=0; j--) {
            img.p[i][j].r = (img.p[i][j].r / img.max_value);
            img.p[i][j].g = (img.p[i][j].g / img.max_value);
            img.p[i][j].b = (img.p[i][j].b / img.max_value);
        }
    }
    img.max_value = 1;
    return img;
}

Image equalize_clamp(Image img, float V)
{
    return equalize(clamp(img, V));
}

Image gammaCurve(Image img, float gamma)
{
    equalize(img);

    img.max_value = 1;

    for (int i = img.h-1; i>=0; i--) {
        for(int j = img.w-1; j>=0; j--) {
            img.p[i][j].r = pow((img.p[i][j].r), 1/gamma);
            img.p[i][j].g = pow((img.p[i][j].g), 1/gamma);
            img.p[i][j].b = pow((img.p[i][j].b), 1/gamma);
            float max_temp = max({img.p[i][j].r,img.p[i][j].g,img.p[i][j].b}); 
            if (img.max_value < max_temp) img.max_value = max_temp;
        }
    }
    return img;
}

Image gammaCurve_clamp(Image img, float gamma, float V)
{
    return clamp(gammaCurve(img, gamma), V);
}

ostream& operator << (ostream& os, const Image& obj) {
    os << "Image with hxw:" << to_string(obj.h)+"x"+to_string(obj.w) 
       << " max_value:" << obj.max_value 
       << " color_res:" << obj.color_res 
       << " pixels:\n";
    for(int i = 0; i<obj.w; i++) {
        for(int j = 0; j<obj.h; j++) {
            os << obj.p[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}
