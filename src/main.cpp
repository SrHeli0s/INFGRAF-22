#include "point/Point.hpp"
#include "vec3/Vec3.hpp"
#include "transformation/Transformation.hpp"
#include "tone_mapping/ppm/PPM.hpp"
#include "tone_mapping/image/Image.hpp"
#include "tone_mapping/rgb/Rgb.hpp"
#include "sphere/Sphere.hpp"
#include <iostream>
using namespace std;

int main() {

    PPM p = PPM();
    // Image antes = p.read("/home/yo/Escritorio/GRAF/HDR PPM files/test.ppm");
    // cout << "Pixeles antes: \n" << antes << "\n\n";

    // Image despues = equalize(antes, antes.max_value);

    // cout << "Pixeles despues: \n" << despues;

    // p.write("/home/yo/Escritorio/GRAF/HDR PPM files/test2.ppm",despues);

    Image test = p.read("/home/yo/Escritorio/GRAF/HDR PPM files/forest_path.ppm");
    
    Image output = equalize_clamp(test,1024);
    p.write("/home/yo/Escritorio/GRAF/HDR PPM files/test2.ppm",output);

    return 0;
}