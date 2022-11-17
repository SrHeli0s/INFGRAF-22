#include "Camera.hpp"
#include "../../point/Point.hpp"
#include "../../vec3/Vec3.hpp"
#include "../../transformation/Transformation.hpp"
#include "../../primitives/Primitive.hpp"
#include "../../primitives/sphere/Sphere.hpp"
#include "../../primitives/plane/Plane.hpp"
#include "../../tone_mapping/image/Image.hpp"
#include "../../utils/Utils.hpp"
#include "../../utils/ConcurrentQueue.hpp"
#include "../ray/Ray.hpp"
#include "../scene/Scene.hpp"
#include "../../tone_mapping/rgb/Rgb.hpp"
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

RGB Camera::getBRDF(Collision col, Vec3 wi) {
    //NOTE: W0 esta dentro de col
    return col.obj->getEmission(col.collision_point) / M_PI;
}

RGB Camera::nextLevelEstimation(Collision col, Scene scene) 
{
    RGB output = RGB(0,0,0);
    for (auto l: scene.lights) {
        float distance_to_light = (mod(l.center - col.collision_point));
        Vec3 W_i = (l.center-col.collision_point)/distance_to_light;
        //Calculate shadows
        Ray shadow = Ray(col.collision_point,W_i);
        Collision closest = closest_col(shadow,scene);
        
        RGB color = RGB(0,0,0);
        if (col.obj != nullptr) {
            //Calculate contributions
            RGB matC = getBRDF(col, normalize(shadow.v));
            float geoC = col.collision_normal * W_i;
            if (geoC<0) geoC = 0; //If is negative is pointing the other way -> It should be black
            RGB lightC = l.power/(float)(pow(distance_to_light,2));
            if (closest.distance>distance_to_light) {                 
                output = output +lightC*matC*geoC;
            }
        }
    }

    return output;
}

RGB Camera::getColor(Ray r, Scene s) {
    RGB output = RGB(0,0,0);

    Collision c = closest_col(r,s);
    if (c.obj != nullptr) {
        output = nextLevelEstimation(c, s);

        float randInclination = acos(sqrt(1-(rand()/(float) (RAND_MAX))));
        float randAzimuth = 2*M_PI*(rand()/(float) (RAND_MAX));

        Vec3 om = normalize(Vec3(sin(randInclination) * cos(randAzimuth),
                                 sin(randInclination) * sin(randAzimuth),
                                 cos(randInclination)));
        
        Vec3 p = perpendicular(c.collision_normal);

        Transformation t1 = BaseChangeTransform(cross(p,c.collision_normal),c.collision_normal,p,c.collision_point);
        Transformation t2 = t1.inverse();

        Vec3 dir = om.applyTransformation(t2);

        Ray newr = Ray(c.collision_point,dir);

        output = output + getColor(newr, s);

    // Vector3 perp = perpendicular(n);
    // Coordinate global2Local(cross(perp, n), perp, n, x, 1);
    // Coordinate dir(Vector3(1,0,0), Vector3(0,1,0), Vector3(0,0,1), omega, 0);

    // Coordinate local2Global = inverseTransformation(global2Local);

    // Vector3 globalDir = local2Global(dir).getPosition();

    // return { globalDir, eval(x, globalDir, omega0) };

    }
    return output;
} 


RGB Camera::renderPixel(Scene scene, unsigned int column, unsigned int row, unsigned int nRays)
{
    vector<RGB> colors;
    Vec3 pixel = this->f + this->l + this->u; // upper-left pixel
    
    for (int y = 0; y<nRays; y++) {
        Ray ray = Ray(this->o, pixel + pixel_right*(column+(rand()/(float) (RAND_MAX))) + pixel_down*(row+(rand()/(float) (RAND_MAX))));
        // Ray ray = Ray(this->o, normalize(this->f));
        colors.push_back(getColor(ray,scene));
    }

    //Calculate average
    RGB average_rgb = RGB(0,0,0);

    for(RGB c : colors) {
        average_rgb = average_rgb + c;
    }
    average_rgb = average_rgb / colors.size();

    return average_rgb;

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
