#include "point/Point.hpp"
#include "vec3/Vec3.hpp"
#include "transformation/Transformation.hpp"
#include "tone_mapping/ppm/PPM.hpp"
#include "tone_mapping/image/Image.hpp"
#include "tone_mapping/rgb/Rgb.hpp"
#include "primitives/sphere/Sphere.hpp"
#include "primitives/plane/Plane.hpp"
#include "primitives/triangle/Triangle.hpp"
#include "primitives/stl/Stl.hpp"
#include "primitives/sprite/Sprite.hpp"
#include "render/ray/Ray.hpp"
#include "render/camera/Camera.hpp"
#include "render/scene/Scene.hpp"
#include <iostream>
#include <chrono>
#include <time.h>
using namespace std;

void gammaAndWrite(Image x, float n, string name) {
    PPM p = PPM();
    Image adjusted = gammaCurve(x,n);
    p.write((name+"_"+to_string(n)+".ppm").c_str(),adjusted);
}

Scene getS1() {
    Scene sc = Scene();
    Material red = Material(RGB(0.8,0,0),RGB(),RGB(),RGB(),1);
    Material green = Material(RGB(0,0.8,0),RGB(),RGB(),RGB(),1);
    Material luz = LightMat(RGB(1,1,1));
    Material metal = Material(RGB(),RGB(0.2,0.2,0.9),RGB(),RGB(),1);
    Material glass = Material(RGB(),RGB(),RGB(0.9,0.9,0.9),RGB(),1.5);
    //Camera
    sc.cam = Camera(Point(0,0,-3.5),Vec3(0,1,0),Vec3(-1,0,0),Vec3(0,0,3),255,255);
    //Planes
    sc.addP(Plane(1,Vec3(1,0,0),red));      //left
    sc.addP(Plane(1,Vec3(-1,0,0),green));   //right
    sc.addP(Plane(1,Vec3(0,1,0)));          //floor
    sc.addP(Plane(1,Vec3(0,-1,0)));     //ceiling
    sc.addP(Plane(1,Vec3(0,0,-1)));         //back
    //Spheres
    sc.addP(Sphere(Point(-0.5,-0.7,0.25),Vec3(0,0.6,0),Point(-0.2,-0.7,0.25), metal));
    sc.addP(Sphere(Point(0.5,-0.7,-0.25),Vec3(0,0.6,0),Point(0.8,-0.7,0.25), glass));
    //Light
    sc.addL(PointLight(Point(0,0.5,0),RGB(1,1,1)));

    return sc;
}

Scene getS2() {
    Scene sc = Scene();
    //Camera
    sc.cam = Camera(Point(0,0,-3.5),Vec3(0,1,0),Vec3(-1,0,0),Vec3(0,0,1),256,256);
    //Planes
    sc.addP(Plane(5,Vec3(0,0,-1))); //Back
    //Sprites
    sc.addP(Sprite(Point(2,1,0),Vec3(1,0,-1),Vec3(0,-1,0),"../resources/image.ppm",50));
    sc.addP(Sprite(Point(2,2,-1),Vec3(-0.5,0,-1),Vec3(0,-1,0),"../resources/image2.ppm",75));
    //Light
    sc.addL(PointLight(Point(1.5,0.5,-3.5),RGB(1,1,1)));

    return sc;
}

Scene getS3() {
    Scene sc = Scene();
    Material red = Material(RGB(0.5,0,0),RGB(),RGB(),RGB(),1);
    Material green = Material(RGB(0,0.5,0),RGB(),RGB(),RGB(),1);
    //Camera
    sc.cam = Camera(Point(-3.5,0,-3.5),Vec3(0,1,0),Vec3(-1,0,0),Vec3(1,0,1),256,256);
    //Planes
    sc.addP(Plane(5,Vec3(0,0,-1))); //Back
    //Sprites
    sc.addP(STL("../resources/test.stl",Point(1,-1,0),0.1,red));
    sc.addP(STL("../resources/test.stl",Point(0,-1.5,2),0.25,green));
    //Light
    sc.addL(PointLight(Point(1.5,0.5,-3.5),RGB(1,1,1)));

    return sc;
}


int main() {
    srand(time(NULL));

    Scene sc = getS1();

    
    auto start = chrono::high_resolution_clock::now();
    Image output1 = sc.cam.render(sc,8,1000000);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Time: " << duration.count() << " ms" <<endl;

    cout << "Adjusting and writing..." << endl;

    std::vector<float> gammas = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
                                1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0,
                                2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0,
                                3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0,
                                4.1, 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 4.8, 4.9, 5.0,
                                5.1, 5.2, 5.3, 5.4, 5.5, 5.6, 5.7, 5.8, 5.9, 6.0,
                                6.1, 6.2, 6.3, 6.4, 6.5, 6.6, 6.7, 6.8, 6.9, 7.0,
                                7.1, 7.2, 7.3, 7.4, 7.5, 7.6, 7.7, 7.8, 7.9, 8.0,
                                8.1, 8.2, 8.3, 8.4, 8.5, 8.6, 8.7, 8.8, 8.9, 9.0,
                                9.1, 9.2, 9.3, 9.4, 9.5, 9.6, 9.7, 9.8, 9.9, 10.0,
                                10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99 };
    for (auto i : gammas) {
        gammaAndWrite(output1,i,"test");
    }

    cout << (char)7 << endl;

    return 0;
}