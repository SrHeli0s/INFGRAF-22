#include "PPM.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

PPM::PPM() {}

Image PPM::read(const char* path)
{
    float max_value = -1;
    float color_res;
    unsigned int h, w;
    vector<vector<RGB>> pixels;

    ifs.open(path);

    string buffer = "";

    
    getline(ifs,buffer); //Format

    getline(ifs,buffer); //Max value comment
    if(buffer.substr(0,5) == "#MAX=") {
        sscanf(buffer.c_str(),"#MAX=%f",&max_value);
        getline(ifs,buffer); //Name of file
    }


    getline(ifs,buffer); //Size
    sscanf(buffer.c_str(),"%u %u",&w,&h);

    getline(ifs,buffer); //Max value
    sscanf(buffer.c_str(),"%f",&color_res);
    if (max_value < 0) {
        max_value = color_res;
    }

    //Read the file
    float red, green, blue;
    float conversion = max_value/color_res;

    pixels.resize(h);
    for(int i = 0; i<h; i++) {
        pixels[i].resize(w);
        for(int j = 0; j<w; j++) {
            ifs >> red >> green >> blue;
            pixels[i][j] = RGB(red*conversion,green*conversion,blue*conversion);
        }
    }

    ifs.close();

    return Image(pixels,max_value,color_res);
}

void PPM::write(const char* path, Image img)
{
    ofs.open(path, ofstream::out | ofstream::trunc);
    
    //Write the "headers"
    ofs << "P3\n#MAX="+to_string((long)img.max_value)+"\n# "+path+"\n"+to_string(img.w)+" "+to_string(img.h)+"\n"+to_string((int)img.color_res) << "\n";
    
    //Write the file
    float red, green, blue;
    float conversion = img.color_res/img.max_value;

    for(int i = 0; i < img.h; i++) {
        for(int j = 0; j < img.w; j++) {
            ofs << (long)(img.p[i][j].r*conversion) << " " << (long)(img.p[i][j].g*conversion) << " " << (long)(img.p[i][j].b*conversion) << "\t";
        }
        ofs << "\n";
    }

    ofs.close();
}