#pragma once
#include <iostream>
#include <vector>
#include "../../point/Point.hpp"
#include "../../vec3/Vec3.hpp"
#include "../ray/Ray.hpp"
#include "../../tone_mapping/rgb/Rgb.hpp"
#include "../../primitives/Material.hpp"
#include "../../utils/ConcurrentQueue.hpp"

class Scene;
class Image;
class Ray;

const unsigned int NTHREADS = 4;

struct Pixel 
{
    int i, j;
    RGB color;
};

class Camera {
    private:
        enum Event {
            DIFFUSE = 0,
            SPECULAR = 1,
            REFRACTION = 2,
            ABSORPTION = 3,
            EMMIT = 4
        };
        void worker(ConcurrentQueue<std::pair<int, int>> &jobs, ConcurrentQueue<Pixel> &result, Scene &scene, unsigned int nRays);
        RGB getBRDF(Collision col, Vec3 wi);
        RGB nextEventEstimation(Collision col, Scene scene, Event e);
        Ray nextRay(Collision col, Scene scene, Event e);
        RGB getColor(Ray r, Scene s);
        Vec3 sampleDirRefr(Collision col);
        Event russianRoulette(double t, Material m);

        Vec3 pixel_up;
        Vec3 pixel_down;
        Vec3 pixel_left;
        Vec3 pixel_right;
    public :
        Vec3 sampleDirSpec(Collision col);
        Point o;
        Vec3 u, l, f; //Up, left, foward
        float w,h;  //Size of the image

    Camera();
    Camera(Point o, Vec3 u, Vec3 l, Vec3 f);
    Camera(Point o, Vec3 u, Vec3 l, Vec3 f, float w, float h);

    Image render(Scene scene, unsigned int nRays);
    RGB renderPixel(Scene scene, unsigned int column, unsigned int row, unsigned int nRays = 1);
    
};

std::ostream& operator << (std::ostream& os, const Camera& obj);