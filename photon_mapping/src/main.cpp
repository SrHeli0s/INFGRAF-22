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

int main() {
    srand(time(NULL));

    PPM p = PPM();


    // //========================= SCENE 1 =========================
    // MATERIALS
    Material metal = Material(RGB(),RGB(0.2,0.2,0.8),RGB(),RGB(),1);
    Material glass = Material(RGB(),RGB(),RGB(0.8,0.8,0.8),RGB(),1.5);
    Material red = Material(RGB(0.5,0,0),RGB(),RGB(),RGB(),1);
    Material green = Material(RGB(0,0.5,0),RGB(),RGB(),RGB(),1);
    Material l = LightMat(RGB(1,1,1));
    Plane left = Plane(1,Vec3(1,0,0),red);
    Plane right = Plane(1,Vec3(-1,0,0),green);
    Plane floor = Plane(1,Vec3(0,1,0));
    Plane ceiling = Plane(1,Vec3(0,-1,0),l);
    Plane back = Plane(1,Vec3(0,0,-1));
    
    Sphere A = Sphere(Point(-0.5,-0.7,0.25),Vec3(0,0.6,0),Point(-0.2,-0.7,0.25), metal);
    Sphere B = Sphere(Point(0.5,-0.7,-0.25),Vec3(0,0.6,0),Point(0.8,-0.7,0.25), glass);
    // Triangle t = Triangle(Point(0.5,-0.5,-0.5),Point(0,0.5,-0.5),Point(-0.5,-0.5,-0.5),RGB(0,255,0));

    Camera camera = Camera(Point(0,0,-3.5),Vec3(0,1,0),Vec3(-1,0,0),Vec3(0,0,3),255,255);

    PointLight pl = PointLight(Point(0,0.5,0),RGB(1,1,1));

    Scene sc = Scene();
    sc.addP(left);
    sc.addP(right);
    sc.addP(floor);
    sc.addP(ceiling);
    sc.addP(back);
    sc.addP(A);
    sc.addP(B);
    // sc.addP(t);
    sc.addL(pl);

    
    
    
    //========================= SCENE 2 =========================
    // Plane back = Plane(5,Vec3(0,0,-1),RGB(10,10,10));
    // Sprite sprTest = Sprite(Point(2,1,0),Vec3(1,0,-1),Vec3(0,-1,0),"resources/image.ppm",50);
    // Sprite sprTest2 = Sprite(Point(2,2,-1),Vec3(-0.5,0,-1),Vec3(0,-1,0),"resources/image2.ppm",75,RGB(0,135,98));

    // Camera camera = Camera(Point(0,0,-3.5),Vec3(0,1,0),Vec3(-1,0,0),Vec3(0,0,1),256,256);

    // PointLight pl = PointLight(Point(1.5,0.5,-3.5),RGB(255,255,255));

    // Scene sc = Scene();
    // sc.addP(back);
    // sc.addP(sprTest);
    // sc.addP(sprTest2);
    // sc.addL(pl);



    // ========================= SCENE 3 =========================
    // Plane back = Plane(2,Vec3(0,0,-1),RGB(10,10,10));
    // Plane ceiling = Plane(5,Vec3(0,-1,0));
    // STL stlTest = STL("resources/test.stl",Point(0,0,0),0.02,RGB(0,255,127));
    // // STL stlTest = STL("resources/bulbasur.stl",Point(0,0,0),0.01,RGB(0,255,127));

    // Vec3 f = Vec3(0,0,5);
    // Vec3 u = Vec3(0,1,0);
    // Vec3 l = Vec3(-1,0,0);

    // Transformation t1 = YRotationTransform(0.25);
    // Transformation t2 = XRotationTransform(-0.175);
    // f.applyTransformation(t1);
    // f.applyTransformation(t2);
    // u.applyTransformation(t1);
    // u.applyTransformation(t2);
    // l.applyTransformation(t1);
    // l.applyTransformation(t2);
    
    // Camera camera = Camera(Point(-1,-0.5,-3.5),u,l,f,1024,1024);

    // PointLight pl0 = PointLight(Point(-5,0.5,0),RGB(255,255,255));
    // PointLight pl1 = PointLight(Point(-5,0.5,-5),RGB(255,255,255));
    // // PointLight pl2 = PointLight(Point(5,0.5,0),RGB(255,255,255));
    // // PointLight pl3 = PointLight(Point(5,0.5,5),RGB(255,255,255));

    // Scene sc = Scene();
    
    // sc.addP(stlTest);
    // sc.addP(back);
    // sc.addP(ceiling);

    // sc.addL(pl0);
    // sc.addL(pl1);
    // // sc.addL(pl2);
    // // sc.addL(pl3);


    //========================= SCENE 4 =========================
    // Plane back = Plane(1,Vec3(0,0,-1),RGB(10,10,10));
    
    // Sphere A = Sphere(Point(-0.5,-0.7,0.25),Vec3(0,0.6,0),Point(-0.2,-0.7,0.25),RGB(255,255,0));
    
    // Camera camera = Camera(Point(0,0,-3.5),Vec3(0,1,0),Vec3(-1,0,0),Vec3(0,0,3),256,256);

    // PointLight pl = PointLight(Point(0,0.5,0),RGB(255,255,255));

    // Scene sc = Scene();
    // sc.addP(back);
    // sc.addP(A);
    // sc.addL(pl);




    
    auto start = chrono::high_resolution_clock::now();
    Image output = camera.render(sc,5,100);
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Time: " << duration.count() << " ms" <<endl;
    
    cout << "Adjusting..." << endl;
    Image outputAdjusted = gammaCurve(output,2.2);
    Image outputAdjusted1 = gammaCurve(output,0.5);
    Image outputAdjusted2 = gammaCurve(output,4.2);
    Image outputAdjusted3 = gammaCurve(output,6.2);
    
    cout << "Writing..." << endl;
    p.write("scene.ppm",outputAdjusted);
    p.write("scene1.ppm",outputAdjusted1);
    p.write("scene2.ppm",outputAdjusted2);
    p.write("scene3.ppm",outputAdjusted3);

    return 0;
}