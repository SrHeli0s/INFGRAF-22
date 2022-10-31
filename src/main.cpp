#include "point/Point.hpp"
#include "vec3/Vec3.hpp"
#include "transformation/Transformation.hpp"
#include "tone_mapping/ppm/PPM.hpp"
#include "tone_mapping/image/Image.hpp"
#include "tone_mapping/rgb/Rgb.hpp"
#include "primitives/sphere/Sphere.hpp"
#include "primitives/plane/Plane.hpp"
#include "ray/Ray.hpp"
#include "camera/Camera.hpp"
#include <iostream>
using namespace std;

int main() {

    PPM p = PPM();
    
    // Image test = p.read("/home/yo/Escritorio/GRAF/HDR PPM files/forest_path.ppm");
    
    // Image output = gammaCurve(test, 0.25);

    Plane left = Plane(1,Vec3(1,0,0),RGB(255,0,0));
    Plane right = Plane(1,Vec3(-1,0,0),RGB(0,255,0));
    Plane floor = Plane(1,Vec3(0,1,0));
    Plane ceiling = Plane(1,Vec3(0,-1,0));
    Plane back = Plane(1,Vec3(0,0,-1));
    
    Sphere A = Sphere(Point(-0.5,-0.7,0.25),Vec3(0,0.6,0),Point(-0.2,-0.7,0.25),RGB(255,255,0));
    Sphere B = Sphere(Point(0.5,-0.7,0.25),Vec3(0,0.6,0),Point(0.8,-0.7,0.25),RGB(255,0,127));

    Camera camera = Camera(Point(0,0,3.5),Vec3(0,1,0),Vec3(-1,0,0),Vec3(0,0,3));

    Primitive* scene[7] = {&left, &right, &floor, &ceiling, &back, &A, &B};

    Image output = camera.render(scene,sizeof(scene)/sizeof(scene[0]));
    //                                 ^Size of array
    p.write("scene.ppm",output);

    return 0;
}