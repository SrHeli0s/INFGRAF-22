#include "PPMreader.hpp"
#include <iostream>
#include <fstream>

using namespace std;

PPMreader::PPMreader() {}

PPMreader::PPMreader(const char* path)
{
    int N = 50;
    this->path = path;

    data.open(path);

    char buffer[N] = {};

    data.getline(buffer,N); //Format

    data.getline(buffer,N); //Max value
    sscanf(buffer,"#MAX=%f",&max_value);

    data.getline(buffer,N); //Name of file

    data.getline(buffer,N); //Size
    sscanf(buffer,"%u %u",&w,&h);

    data.getline(buffer,N); //Color resolution
    sscanf(buffer,"%f",&color_res);

    //Read the file
    float red, green, blue;
    float conversion = max_value/color_res;
    p.resize(w);
    for(int i = 0; i<w; i++) {
        p[i].resize(h);
        for(int j = 0; j<h; j++) {
            data >> red >> green >> blue;
            p[i][j] = RGB(red*conversion,green*conversion,blue*conversion);
        }
    }

    data.close();
}

std::ostream& operator << (std::ostream& os, const PPMreader& p) {
    os << "PPMreader with path:" << p.path 
       << " hxw:" << to_string(p.h)+"x"+to_string(p.w) 
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