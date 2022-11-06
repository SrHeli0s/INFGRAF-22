#include "point/Point.hpp"
#include "vec3/Vec3.hpp"
#include "transformation/Transformation.hpp"
#include "tone_mapping/ppm/PPM.hpp"
#include "tone_mapping/image/Image.hpp"
#include "tone_mapping/rgb/Rgb.hpp"
#include "primitives/sphere/Sphere.hpp"
#include "primitives/plane/Plane.hpp"
#include "primitives/triangle/Triangle.hpp"
#include "render/ray/Ray.hpp"
#include "render/camera/Camera.hpp"
#include "render/scene/Scene.hpp"
#include <iostream>
#include <chrono>
#include <time.h>
using namespace std;

int main() {
    srand(time(NULL));

    PPM p = PPM();
    
    // Image test = p.read("/home/yo/Escritorio/GRAF/HDR PPM files/forest_path.ppm");
    
    // Image output = gammaCurve(test, 0.25);

    Plane left = Plane(1,Vec3(1,0,0),RGB(255,0,0));
    Plane right = Plane(1,Vec3(-1,0,0),RGB(0,255,0));
    Plane floor = Plane(1,Vec3(0,1,0));
    Plane ceiling = Plane(1,Vec3(0,-1,0));
    Plane back = Plane(1,Vec3(0,0,-1));
    
    Sphere A = Sphere(Point(-0.5,-0.7,0.25),Vec3(0,0.6,0),Point(-0.2,-0.7,0.25),RGB(255,255,0));
    Sphere B = Sphere(Point(0.5,-0.7,-0.25),Vec3(0,0.6,0),Point(0.8,-0.7,0.25),RGB(255,0,127));

    Triangle t = Triangle(0.5,Point(-0.5,-0.5,-0.5),Point(0.5,-0.5,-0.5),Point(0,0.5,-0.5),Vec3(0,0,-1),RGB(0,255,0));

    Camera camera = Camera(Point(0,0,-3.5),Vec3(0,1,0),Vec3(-1,0,0),Vec3(0,0,3),1024,1024);

    PointLight pl = PointLight(Point(0,0.5,0),RGB(255,255,255));

    Scene sc = Scene();
    sc.addP(left);
    sc.addP(right);
    sc.addP(floor);
    sc.addP(ceiling);
    sc.addP(back);
    sc.addP(A);
    sc.addP(B);
    sc.addL(pl);
    // sc.addP(t);
    
    auto start = chrono::high_resolution_clock::now();
    Image output = camera.render(sc,1);
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Tiempo de render: " << duration.count() << " ms" <<endl;

    Image outputAdjusted = gammaCurve(output,2.2);
    p.write("scene.ppm",outputAdjusted);

    return 0;
}