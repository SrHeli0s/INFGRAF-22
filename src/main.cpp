#include "point/Point.hpp"
#include "vec3/Vec3.hpp"
#include "transformation/Transformation.hpp"
#include "tone_mapping/ppm/PPM.hpp"
#include "tone_mapping/image/Image.hpp"
#include "tone_mapping/rgb/Rgb.hpp"
#include "primitives/sphere/Sphere.hpp"
#include "primitives/plane/Plane.hpp"
#include "ray/Ray.hpp"
#include <iostream>
using namespace std;

int main() {

    // PPM p = PPM();
    
    // Image test = p.read("/home/yo/Escritorio/GRAF/HDR PPM files/forest_path.ppm");
    
    // Image output = gammaCurve(test, 0.25);
    // p.write("/home/yo/Escritorio/GRAF/HDR PPM files/test2.ppm",output);

    Plane p = Plane(1,Vec3(1,0,0));

    Ray r = Ray(Point(0,0,0),Vec3(1,0,0));

    vector<float> i = intersect(r,p);

    cout << i.size() << ": ";
    for (int j = 0; j<i.size(); j++) {
        cout << i[j] << ", ";
    }
    cout << endl;

    return 0;
}