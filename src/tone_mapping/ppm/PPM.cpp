#include "PPM.hpp"
#include <iostream>
#include <fstream>

using namespace std;

PPM::PPM() {}

Image PPM::read(const char* path)
{
    int N = 50;
    float max_value, color_res;
    unsigned int h, w;
    vector<vector<RGB>> pixels;

    ifs.open(path);

    char buffer[N] = {};

    ifs.getline(buffer,N); //Format

    ifs.getline(buffer,N); //Max value
    sscanf(buffer,"#MAX=%f",&max_value);

    ifs.getline(buffer,N); //Name of file

    ifs.getline(buffer,N); //Size
    sscanf(buffer,"%u %u",&w,&h);

    ifs.getline(buffer,N); //Color resolution
    sscanf(buffer,"%f",&color_res);

    //Read the file
    float red, green, blue;
    float conversion = max_value/color_res;
    pixels.resize(w);
    for(int i = 0; i<w; i++) {
        pixels[i].resize(h);
        for(int j = 0; j<h; j++) {
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

    for(int i = 0; i < img.w; i++) {
        for(int j = 0; j < img.h; j++) {
            ofs << (long)(img.p[i][j].r*conversion) << " " << (long)(img.p[i][j].g*conversion) << " " << (long)(img.p[i][j].b*conversion) << "\t";
        }
        ofs << "\n";
    }

    ofs.close();
}