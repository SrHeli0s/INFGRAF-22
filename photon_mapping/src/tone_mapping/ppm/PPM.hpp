#pragma once
#include "../rgb/Rgb.hpp"
#include "../image/Image.hpp"
#include <iostream>
#include <fstream>
#include <vector>

class PPM {
    private:
        std::ifstream ifs;
        std::ofstream ofs;
    public:

    PPM();
    Image read(const char* path);
    void write(const char* path, Image img);
};