#pragma once
#include "../rgb/Rgb.hpp"
#include <iostream>
#include <fstream>
#include <vector>

class Image {
    public:
        float max_value;
        unsigned int h;
        unsigned int w;
        float color_res;
        std::vector<std::vector<RGB>> p;

    Image();
    Image(std::vector<std::vector<RGB>> pixels, float max_value, float color_res);
};

std::ostream& operator << (std::ostream& os, const Image& p);

Image clamp(Image img, float max_clamp = 1);
Image equalize(Image img);
Image gammaCurve(Image img, float gamma);
Image gammaCurve_clamp(Image img, float gamma, float max_clamp);
Image equalize_clamp(Image img, float max_clamp);