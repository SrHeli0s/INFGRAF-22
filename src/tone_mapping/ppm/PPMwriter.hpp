#pragma once
#include "../rgb/Rgb.hpp"
#include "PPMreader.hpp"
#include <iostream>
#include <fstream>
#include <vector>

class PPMwriter {
    public:
        std::ofstream data;
        const char* path;
        float max_value;
        unsigned int h;
        unsigned int w;
        float color_res;
        std::vector<std::vector<RGB>> p;

    PPMwriter();
    PPMwriter(const char* path, unsigned int width, unsigned int height, float maxValue, float colorResolution, std::vector<std::vector<RGB>> p);
};

std::ostream& operator << (std::ostream& os, const PPMwriter& p);