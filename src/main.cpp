#include "point/Point.hpp"
#include "vec3/Vec3.hpp"
#include "transformation/Transformation.hpp"
#include "tone_mapping/ppm/PPMreader.hpp"
#include "tone_mapping/ppm/PPMwriter.hpp"
#include "tone_mapping/rgb/Rgb.hpp"
#include "sphere/Sphere.hpp"
#include <iostream>
using namespace std;

int main() {

    PPMreader p = PPMreader("/home/yo/Escritorio/GRAF/HDR PPM files/seymour_park.ppm");

    PPMwriter writer = PPMwriter("/home/yo/Escritorio/GRAF/HDR PPM files/parquepolla.ppm", p.w, p.h, p.max_value, p.color_res, p.p);
    return 0;
}