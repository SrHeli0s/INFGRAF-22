#pragma once
#include "../rgb/Rgb.hpp"
#include <iostream>
#include <fstream>
#include <vector>

class PPMreader {
    public:
        std::ifstream data;
        const char* path;
        float max_value;
        unsigned int h;
        unsigned int w;
        float color_res;
        std::vector<std::vector<RGB>> p;

    PPMreader();
    PPMreader(const char* path);
};

std::ostream& operator << (std::ostream& os, const PPMreader& p);