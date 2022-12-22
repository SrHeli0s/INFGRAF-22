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
#include "../../photon/Photon.hpp"
#include "../../utils/kdtree.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <thread> // std::thread
#include <functional> // std::ref
#include <algorithm>
#include <chrono>

using PhotonMap = nn::KDTree<Photon,3,PhotonAxisPosition>;

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


RGB Camera::getBRDF(Collision col, Vec3 wi, PhotonMap pm) {
    cout << "THREAD:" << this_thread::get_id() << " HACE SEARCH" << endl;
    vector<const Photon*> nearPhotons = search_nearest(pm, col.collision_point, 0.1);
    cout << "THREAD:" << this_thread::get_id() << " RECIBIDO " << nearPhotons.size() << nearPhotons[0] << endl; 
    cout << *nearPhotons[0] << " " << *nearPhotons[1] << " " << *nearPhotons[2] << endl;
    
    RGB output = RGB();
    for (int i = 0; i<nearPhotons.size(); i++) {
        cout << "THREAD:" << this_thread::get_id() << " ITERACION: " << i << " de " << nearPhotons.size() << " " << *nearPhotons[i] << endl;
        output = output + nearPhotons[i]->flux;
    }
    if (nearPhotons.size() != 0) {
        return output / nearPhotons.size();
    }
    return output;
}

RGB Camera::nextEventEstimation(Collision col, Scene scene, PhotonMap pm, Event e) 
{
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

                RGB matC = getBRDF(col, normalize(shadow.v),pm);
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
        float randInclination = acos(sqrt(1-(rand()/(float) (RAND_MAX))));
        float randAzimuth = 2*M_PI*(rand()/(float) (RAND_MAX));

        Vec3 om = Vec3(sin(randInclination) * cos(randAzimuth),
                        sin(randInclination) * sin(randAzimuth),
                        cos(randInclination));
        
        Vec3 n = col.collision_normal;
        
        Vec3 p = perpendicular(n);

        Transformation t1 = BaseChangeTransform(cross(n,p),n,p,col.collision_point);
        Transformation t2 = t1.inverse();

        Vec3 dir = om.applyTransformation(t2);

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

RGB Camera::getColor(Ray r, Scene s, PhotonMap pm) {
    Collision c = closest_col(r,s);
    RGB output = RGB(0,0,0);
    if (c.obj != nullptr) {
        Event e = russianRoulette(rand()/(float)(RAND_MAX),c.obj->material);
        //Ld
        output = output + nextEventEstimation(c,s,pm,e);
        //Li
        if (e != ABSORPTION) {
            Ray nextR = nextRay(c,s,e);
            if(e==DIFFUSE) {
                output = output + getBRDF(c, nextR.v,pm) * getColor(nextR,s,pm) * M_PI;
            }
            else {
                output = output + getBRDF(c, nextR.v,pm) * getColor(nextR,s,pm);
            }
        }
    }
    return output;
} 


RGB Camera::renderPixel(Scene scene, PhotonMap pm, unsigned int column, unsigned int row, unsigned int nRays)
{
    Vec3 pixel = this->f + this->l + this->u; // upper-left pixel
    
    RGB average_rgb = RGB(0,0,0);
    for (int y = 0; y<nRays; y++) {
        Ray ray = Ray(this->o, pixel + pixel_right*(column+(rand()/(float) (RAND_MAX))) + pixel_down*(row+(rand()/(float) (RAND_MAX))));
        // Ray ray = Ray(this->o, normalize(this->f));
        average_rgb = average_rgb + getColor(ray,scene, pm);
    }
    //Calculate average
    average_rgb = average_rgb / nRays;

    return average_rgb;
}

void Camera::worker(ConcurrentQueue<pair<int,int>> &jobs, ConcurrentQueue<Pixel> &result, Scene &scene, unsigned int nRays, PhotonMap pm)
{
    pair<int, int> n;
    n = jobs.pop();
    while (n.first >= 0 && n.second >= 0) //A value less than 0 marks the end of the list
    {
        Pixel calculated = {n.first,n.second,renderPixel(scene,pm,n.first,n.second,nRays)};
        result.push(calculated);
        n = jobs.pop();
    }
    return;
}


Image Camera::render(Scene scene, unsigned int nRays, unsigned int nPhoton)
{
    Image output;
    output.w = this->w;
    output.h = this->h;
    output.color_res = 255;
    
    cout << "Calculating photons... "; 

    float sum_lights = 0;
    for (auto l: scene.lights) {
        sum_lights = sum_lights +l.power.maxChannel();
    }

    vector<Photon> photons;
    
    for (auto l: scene.lights) {
        unsigned int limit = nPhoton*(l.power.maxChannel()/sum_lights);
        for (unsigned int i = 0; i<limit; i++) {
            RGB color = l.power;
            Point origin = l.center;
            unsigned int x = 0;
            float randInclination = acos(2*(rand()/(float) (RAND_MAX)) - 1);
            float randAzimuth = 2*M_PI*(rand()/(float) (RAND_MAX));

            Vec3 dir = Vec3(sin(randInclination) * cos(randAzimuth),
                            sin(randInclination) * sin(randAzimuth),
                            cos(randInclination));

            Ray r = Ray(origin, dir);

            while (color != RGB(0,0,0)) {
                Collision c = closest_col(r,scene);

                if (c.obj == nullptr) {
                    color = RGB(0,0,0);
                }
                else {
                    Event e = russianRoulette(rand()/(float)(RAND_MAX), c.obj->material);
                    if(e == DIFFUSE) {
                        color = color * c.obj->getEmission(c.collision_point);
                        if(color == RGB(0,0,0)) break;
                        photons.push_back(Photon(c.collision_point,color*4*M_PI/limit));
                        origin = c.collision_point;
                        float randInclination = acos(sqrt(1-(rand()/(float) (RAND_MAX))));
                        float randAzimuth = 2*M_PI*(rand()/(float) (RAND_MAX));

                        Vec3 om = Vec3(sin(randInclination) * cos(randAzimuth),
                                        sin(randInclination) * sin(randAzimuth),
                                        cos(randInclination));
                        
                        Vec3 n = c.collision_normal;
                        
                        Vec3 p = perpendicular(n);

                        Transformation t1 = BaseChangeTransform(cross(n,p),n,p,c.collision_point);
                        Transformation t2 = t1.inverse();

                        Vec3 dir = om.applyTransformation(t2);

                        r = Ray(c.collision_point,normalize(dir));
                    }
                    else if (e == SPECULAR) { //Generate next ray of specular        
                        Material m = c.obj->material;

                        RGB dif = m.kd > 0 ? m.dif / M_PI / m.kd : RGB();
                        RGB spec = m.ks > 0 ? m.spec * (delta(r.v, sampleDirSpec(c))) / m.ks : RGB();
                        RGB refr = m.kt > 0 ? m.refr * (delta(r.v, sampleDirRefr(c))) / m.kt : RGB();

                        color = color * (dif+spec+refr);
                        r = Ray(c.collision_point,sampleDirSpec(c));
                    }
                    else if (e == REFRACTION) { //Generate next ray of refraction
                        Material m = c.obj->material;

                        RGB dif = m.kd > 0 ? m.dif / M_PI / m.kd : RGB();
                        RGB spec = m.ks > 0 ? m.spec * (delta(r.v, sampleDirSpec(c))) / m.ks : RGB();
                        RGB refr = m.kt > 0 ? m.refr * (delta(r.v, sampleDirRefr(c))) / m.kt : RGB();

                        color = color * (dif+spec+refr);
                        r = Ray(c.collision_point, sampleDirRefr(c));
                    }
                    else { //ABSORB
                        color = RGB(0,0,0);
                    }
                }
            }
        }
    }

    PhotonMap map = PhotonMap(photons, PhotonAxisPosition());

    cout << photons.size() << " Photons" << endl;
    cout << "Rendering..." << endl; 


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

    size_t ntrabajos = jobs.size();
    //Prepare output.p
    for(int i = 0; i<this->h; i++) {
        vector<RGB> row;
        output.p.push_back(row);
        for(int j = 0; j<this->w; j++) output.p[i].push_back(RGB(0,0,0));
    }


    //Call threads
    vector<thread> threads;
    for (int i = 0; i<NTHREADS; i++) {
        threads.push_back(std::thread([&](ConcurrentQueue<pair<int,int>> &jobs, ConcurrentQueue<Pixel> &result, Scene &scene, unsigned int nRays, PhotonMap pm){ worker(jobs,result,scene,nRays,pm); }, std::ref(jobs),std::ref(result),std::ref(scene), nRays, map));
    }

    // bool running = true;
    // while(running) {
    //     size_t tam = jobs.size();
    //     cout << "\rDone " << ntrabajos-tam<< " of " << ntrabajos;
    //     cout.flush();
    //     this_thread::sleep_for(std::chrono::milliseconds(1000));
    //     if(tam < NTHREADS) running = false;
    // }
    // cout << endl;


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

    return output;
}

vector<const Photon*> Camera::search_nearest(PhotonMap map, Point p, float r){
    return map.nearest_neighbors(p, 100, r);
}
