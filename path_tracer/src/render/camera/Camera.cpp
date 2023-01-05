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
#include <algorithm>


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

Camera::Event Camera::russianRoulette(double t, Material m) {
    if(m.ke > 0) return EMMIT;
    if ( t < m.kd ) {
        return DIFFUSE;
    } else if ( t < m.kd + m.ks ) {
        return SPECULAR;
    } else if ( t < m.kd + m.ks + m.kt ) {
        return REFRACTION;
    } else {
        return ABSORPTION;
    }
}


RGB Camera::getBRDF(Collision col, Vec3 wi) {
    Material m = col.obj->material;

    if(m.ke > 0) return m.emission;

    RGB dif = m.kd > 0 ? col.obj->getDiffusion(col.collision_point) / M_PI / m.kd : RGB();
    RGB spec = m.ks > 0 ? m.spec * (delta(wi, sampleDirSpec(col))) / m.ks : RGB();
    RGB refr = m.kt > 0 ? m.refr * (delta(wi, sampleDirRefr(col))) / m.kt : RGB();

    return dif+spec+refr;
}

RGB Camera::nextEventEstimation(Collision col, Scene scene, Event e) 
{
    Material m = col.obj->material;
    RGB output;
    if (e == DIFFUSE) { //Generate color of diffuse
        output = RGB(0,0,0);
        for (auto l: scene.lights) {
            float distance_to_light = (mod(l.center - col.collision_point));
            Vec3 W_i = (l.center-col.collision_point)/distance_to_light;
            //Calculate shadows
            Ray shadow = Ray(col.collision_point,W_i);
            Collision closest = closest_col(shadow,scene);
            
            RGB color = RGB(0,0,0);
            if (col.obj != nullptr) {
                Material m = col.obj->material;
                Vec3 omI = normalize(shadow.v);
                //Calculate contributions
                RGB dif = m.kd > 0 ? m.dif / M_PI / m.kd : RGB();
                RGB spec = m.ks > 0 ? m.spec * (delta(omI, sampleDirSpec(col))) / m.ks : RGB();
                RGB refr = m.kt > 0 ? m.refr * (delta(omI, sampleDirRefr(col))) / m.kt : RGB();

                RGB matC = getBRDF(col, normalize(shadow.v));
                float geoC = col.collision_normal * W_i;
                if (geoC<0) geoC = 0; //If is negative is pointing the other way -> It should be black
                RGB lightC = l.power/(float)(pow(distance_to_light,2));
                if (closest.distance>distance_to_light) {                 
                    output = output + lightC*matC*geoC;
                }
            }
        }
    }
    else if (e == SPECULAR) { //Generate color of specular
        output = RGB(0,0,0);
    }
    else if (e == REFRACTION) {
        output = RGB(0,0,0);
    }
    else { //ABSORB
        output = RGB(0,0,0);
    }

    return output;
}

Vec3 Camera::sampleDirSpec(Collision col) {
    return normalize(normalize(col.r.v) - normalize(col.collision_normal)*(normalize(col.r.v)*normalize(col.collision_normal))*2);
}

Vec3 Camera::sampleDirRefr(Collision col) {
    Vec3 w_i = normalize(col.r.v);
    Vec3 n;
    float refraction_ratio;
    if (w_i * normalize(col.collision_normal) < 0) { //We are outside of the object
        refraction_ratio = 1.0/col.obj->material.ri;
        n = normalize(col.collision_normal);
    }
    else { //We are inside of the object
        refraction_ratio = col.obj->material.ri;
        n = normalize(col.collision_normal)*(-1.0);
    }

    float cos_theta = inverse(w_i) * n;
    float sin_theta = sqrt(1.0 - cos_theta*cos_theta);
    if (refraction_ratio * sin_theta > 1.0) {
        return sampleDirSpec(col);
    }
    else {
        Vec3 out_perp =  (w_i + n*cos_theta) * refraction_ratio;
        Vec3 out_parallel = n * -sqrt(1.0 - pow(mod(out_perp),2));
        return out_perp + out_parallel;
    }
}

Ray Camera::nextRay(Collision col, Scene scene, Event e) {
    Ray output;

    Material m = col.obj->material;
    if (e == DIFFUSE) { //Generate next ray of diffuse
        float randInclination = acos(sqrt(1.0-(rand()/(float) (RAND_MAX))));
        float randAzimuth = 2*M_PI*(rand()/(float) (RAND_MAX));

        Vec3 om = Vec3(sin(randInclination) * cos(randAzimuth),
                        sin(randInclination) * sin(randAzimuth),
                        cos(randInclination));
        
        Vec3 n = col.collision_normal;
        
        Vec3 p = perpendicular(n);
        Vec3 v2 = cross(p, n);
        Vec3 v3 = cross(v2, n);
        
        Transformation t1 = BaseChangeTransform(v2,v3,n,col.collision_point);
        // Transformation t2 = t1.inverse();

        Vec3 dir = om.applyTransformation(t1);

        output = Ray(col.collision_point,normalize(dir));
    }
    else if (e == SPECULAR) { //Generate next ray of specular        
        output = Ray(col.collision_point,sampleDirSpec(col));
    }
    else if (e == REFRACTION) { //Generate next ray of refraction
        output = Ray(col.collision_point, sampleDirRefr(col));
    }
    else { //ABSORTION
        output = Ray(Point(0,0,0),Vec3(0,0,0));
    }
    
    return output;

}

RGB Camera::getColor(Ray r, Scene s) {
    Collision c = closest_col(r,s);
    RGB output = RGB(0,0,0);
    if (c.obj != nullptr) {
        Event e = russianRoulette(rand()/(float)(RAND_MAX),c.obj->material);
        //Ld
        output = output + nextEventEstimation(c,s,e);
        //Li
        if (e != ABSORPTION) {
            Ray nextR = nextRay(c,s,e);
            if(e==DIFFUSE) {
                output = output + getBRDF(c, nextR.v) * getColor(nextR,s) * M_PI;
            }
            else if(e == EMMIT) {
                output = output + getBRDF(c, nextR.v);
            }
            else {
                output = output + getBRDF(c, nextR.v) * getColor(nextR,s);
            }
        }
    }
    return output;
} 


RGB Camera::renderPixel(Scene scene, unsigned int column, unsigned int row, unsigned int nRays)
{
    Vec3 pixel = this->f + this->l + this->u; // upper-left pixel
    
    RGB average_rgb = RGB(0,0,0);
    for (int y = 0; y<nRays; y++) {
        Ray ray = Ray(this->o, pixel + pixel_right*(column+(rand()/(float) (RAND_MAX))) + pixel_down*(row+(rand()/(float) (RAND_MAX))));
        // Ray ray = Ray(this->o, normalize(this->f));
        average_rgb = average_rgb + getColor(ray,scene);
    }
    //Calculate average
    average_rgb = average_rgb / nRays;

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
