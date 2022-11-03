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
        Ray rayo = Ray(this->o, pixel + pixel_right*(column+(rand()/(float) (RAND_MAX))) + pixel_down*(this->h-row-1+(rand()/(float) (RAND_MAX))));

        float nearest_distance = INFINITY;
        RGB nearest_rgb = RGB(0,0,0);
        for (int x = 0; x<scene.objs.size(); x++) {
            vector<float> distances = scene.objs[x]->intersect(rayo);
            for (int k = 0; k < distances.size(); k++) {
                if(distances[k] < nearest_distance) {
                    nearest_rgb = scene.objs[x]->emission;
                    nearest_distance = distances[k];
                }
            }
        }
        colors.push_back(nearest_rgb);
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
}

void Camera::worker(ConcurrentQueue<pair<unsigned int, unsigned int>> &jobs, ConcurrentQueue<Pixel> &result, Scene scene, unsigned int nRays)
{
    pair<unsigned int, unsigned int> n;
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
    ConcurrentQueue<pair<unsigned int, unsigned int>> jobs;
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
        std::thread t(&Camera::worker,std::ref(jobs),std::ref(result),scene,nRays);
        threads.push_back(t);
    }

    //Wait for end
    for (int i = 0; i<NTHREADS; i++) {
        threads[i].join();
    }

    queue<Pixel> qresult = result.getQueue();

    while (!qresult.empty())
    {
        Pixel a = qresult.front();

        output.p[a.i][a.j] = a.color;
        //Set output.maxvalue to the max of average_rgb.r, average_rgb.g, average_rgb.b and output.maxvalue
        output.max_value = (a.color.r>output.max_value) ? a.color.r : ((a.color.g>output.max_value) ? a.color.g : ((a.color.b>output.max_value) ? a.color.b : output.max_value));

        qresult.pop();
    }

    
    // output.p[i].push_back(average_rgb);

    return output;
}
