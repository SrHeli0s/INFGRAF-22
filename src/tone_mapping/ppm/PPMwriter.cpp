#include "PPMwriter.hpp"
#include "PPMreader.hpp"
#include <iostream>
#include <fstream>

using namespace std;

PPMwriter::PPMwriter() {}

PPMwriter::PPMwriter(const char* path, unsigned int width, unsigned int height, float maxValue, float colorResolution, vector<vector<RGB>> p)
{
    w = width;
    h = height;
    max_value = maxValue;
    color_res = colorResolution;

    data.open(path, ofstream::out | ofstream::trunc);
    
    //Write the "headers"
    data << "P3\n#MAX="+to_string((long)max_value)+"\n# "+path+"\n"+to_string(w)+" "+to_string(h)+"\n"+to_string((int)color_res) << "\n";
    
    //Write the file
    float red, green, blue;
    float conversion = color_res/max_value;

    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            data << (long)(p[i][j].r*conversion) << " " << (long)(p[i][j].g*conversion) << " " << (long)(p[i][j].b*conversion) << "\t";
        }
        data << "\n";
    }

    data.close();
}

std::ostream& operator << (std::ostream& os, const PPMwriter& p) {
    os << "PPMwriter with path:" << p.path 
       << " hxw:" << to_string(p.h)+"x"+to_string(p.w) 
       << " max_value:" << p.max_value 
       << " color_res:" << p.color_res;
    return os;
}