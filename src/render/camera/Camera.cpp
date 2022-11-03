#include "Camera.hpp"
#include "../../point/Point.hpp"
#include "../../vec3/Vec3.hpp"
#include "../../primitives/Primitive.hpp"
#include "../../primitives/sphere/Sphere.hpp"
#include "../../primitives/plane/Plane.hpp"
#include "../../tone_mapping/image/Image.hpp"
#include "../../utils/Utils.hpp"
#include "../../utils/ConcurrentQueue.hpp"
#include "../ray/Ray.hpp"
#include "../scene/Scene.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <thread> // std::thread
#include <functional> // std::ref


using namespace std;

Camera::Camera() {}

Camera::Camera(Point o, Vec3 u, Vec3 l, Vec3 f, float w, float h)
{
    this->o = o;
    this->u = u;
    this->l = l;
    this->f = f;
    this->w = w;
    this->h = h;
    this->pixel_up = this->u / (this->h/2);
    this->pixel_down = inverse(pixel_up);
    this->pixel_left = this->l / (this->w/2);
    this->pixel_right = inverse(pixel_left);
}

Camera::Camera(Point o, Vec3 u, Vec3 l, Vec3 f)
{
    this->o = o;
    this->u = u;
    this->l = l;
    this->f = f;
    this->w = 256;
    this->h = 256;
    this->pixel_up = this->u / (this->h/2);
    this->pixel_down = inverse(pixel_up);
    this->pixel_left = this->l / (this->w/2);
    this->pixel_right = inverse(pixel_left);
}

ostream& operator << (ostream& os, const Camera& obj)
{
    os << "Camera(origin=" << obj.o << ", up=" << obj.u << ", left=" << obj.l
    << ", foward=" << obj.f << ", wxh=" << obj.w << "x" << obj.h << ")";
    return os;
}

RGB Camera::renderPixel(Scene scene, unsigned int column, unsigned int row, unsigned int nRays)
{
    vector<RGB> colors;
    Vec3 pixel = this->f + this->l + this->u; // upper-left pixel
    
    for (int y = 0; y<nRays; y++) {
        Ray rayo = Ray(this->o, pixel + pixel_right*(column+(rand()/(float) (RAND_MAX))) + pixel_down*(row+(rand()/(float) (RAND_MAX))));

        Collision nearest_collision = {nullptr,Point(0,0,0),INFINITY};
        for (int x = 0; x<scene.objs.size(); x++) {
            vector<Collision> collisions = scene.objs[x]->intersect(rayo);
            for (int k = 0; k < collisions.size(); k++) {
                if(collisions[k].distance < nearest_collision.distance) {
                    nearest_collision = collisions[k];
                }
            }
        }
        colors.push_back(nearest_collision.obj->emission);
    }

    //Calculate average
    RGB average_rgb = RGB(0,0,0);

    for(RGB c : colors) {
        average_rgb.r += c.r;
        average_rgb.g += c.g;
        average_rgb.b += c.b;
    }

    average_rgb.r /= colors.size();
    average_rgb.g /= colors.size();
    average_rgb.b /= colors.size();

    return average_rgb;

    // Point hit = rayo.p + (rayo.v * nearest_distance);
    // RGB sum = RGB(0,0,0);
    // //P4
    // for (auto l: scene.lights) {
    //     sum = sum + (l.power)/(float)(pow(mod(l.center - hit),2));
    //     float x = ((l.center-hit)/(mod(l.center - hit)));
    // }
}

void Camera::worker(ConcurrentQueue<pair<int,int>> &jobs, ConcurrentQueue<Pixel> &result, Scene &scene, unsigned int nRays)
{
    pair<int, int> n;
    n = jobs.pop();
    while (n.first >= 0 && n.second >= 0) //A value less than 0 marks the end of the list
    {
        Pixel calculated = {n.first,n.second,renderPixel(scene,n.first,n.second,nRays)};
        result.push(calculated);
        n = jobs.pop();
    }
    return;
}


Image Camera::render(Scene scene, unsigned int nRays = 1)
{
    Image output;
    output.w = this->w;
    output.h = this->h;
    output.color_res = 255;
    ConcurrentQueue<pair<int,int>> jobs;
    ConcurrentQueue<Pixel> result;

    //Create jobs
    for(int i = 0; i<this->h; i++) {
        for(int j = 0; j<this->w; j++) {
            jobs.push(make_pair(i, j));
        }
    }
    for(int i = 0; i<NTHREADS; i++) {
        jobs.push(make_pair(-1,-1));
    }

    //Prepare output.p
    for(int i = 0; i<this->h; i++) {
        vector<RGB> row;
        output.p.push_back(row);
        for(int j = 0; j<this->w; j++) output.p[i].push_back(RGB(0,0,0));
    }


    //Call threads
    vector<thread> threads;
    for (int i = 0; i<NTHREADS; i++) {
        // threads.push_back(std::thread(&Camera::worker,std::ref(jobs),std::ref(result),std::ref(scene),nRays));
        threads.push_back(std::thread([&](ConcurrentQueue<pair<int,int>> &jobs, ConcurrentQueue<Pixel> &result, Scene &scene, unsigned int nRays){ worker(jobs,result,scene,nRays); }, std::ref(jobs),std::ref(result),std::ref(scene),nRays));
    }

    //Wait for end
    for (auto &th : threads) {
        th.join();
    }

    queue<Pixel> qresult = result.getQueue();

    while (!qresult.empty())
    {
        Pixel a = qresult.front();

        output.p[a.j][a.i] = a.color;
        //Set output.maxvalue to the max of average_rgb.r, average_rgb.g, average_rgb.b and output.maxvalue
        output.max_value = (a.color.r>output.max_value) ? a.color.r : ((a.color.g>output.max_value) ? a.color.g : ((a.color.b>output.max_value) ? a.color.b : output.max_value));

        qresult.pop();

    }

    // output.p[i].push_back(average_rgb);

    return output;
}
