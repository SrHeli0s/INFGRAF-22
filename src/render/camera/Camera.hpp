#pragma once
#include <iostream>
#include <vector>
#include "../../point/Point.hpp"
#include "../../vec3/Vec3.hpp"
#include "../../tone_mapping/rgb/Rgb.hpp"
#include "../../utils/ConcurrentQueue.hpp"

class Scene;
class Image;

const unsigned int NTHREADS = 5;

struct Pixel 
{
    int i, j;
    RGB color;
};

class Camera {
    private:
        Vec3 pixel_up;
        Vec3 pixel_down;
        Vec3 pixel_left;
        Vec3 pixel_right;
    public :
        Point o;
        Vec3 u, l, f; //Up, left, foward
        float w,h;  //Size of the image

    Camera();
    Camera(Point o, Vec3 u, Vec3 l, Vec3 f);
    Camera(Point o, Vec3 u, Vec3 l, Vec3 f, float w, float h);

    Image render(Scene scene, unsigned int nRays);
    RGB renderPixel(Scene scene, unsigned int column, unsigned int row, unsigned int nRays = 1);
    
    private:
        void worker(ConcurrentQueue<std::pair<int, int>> &jobs, ConcurrentQueue<Pixel> &result, Scene &scene, unsigned int nRays);

};

std::ostream& operator << (std::ostream& os, const Camera& obj);