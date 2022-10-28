#include "Camera.hpp"
#include "../point/Point.hpp"
#include "../vec3/Vec3.hpp"
#include "../primitives/sphere/Sphere.hpp"
#include "../primitives/plane/Plane.hpp"
#include "../tone_mapping/image/Image.hpp"
#include "../utils/Utils.hpp"
#include "../primitives/Primitive.hpp"
#include "../ray/Ray.hpp"
#include <iostream>
#include <vector>
#include <cmath>


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
}

Camera::Camera(Point o, Vec3 u, Vec3 l, Vec3 f)
{
    this->o = o;
    this->u = u;
    this->l = l;
    this->f = f;
    this->w = 256;
    this->h = 256;
}

ostream& operator << (ostream& os, const Camera& c)
{
    os << "Camera(origin=" << c.o << ", up=" << c.u << ", left=" << c.l
    << ", foward=" << c.f << ", wxh=" << c.w << "x" << c.h << ")";
    return os;
}

Image Camera::render(vector<Primitive> scene)
{
    Image output;
    output.w = this->w;
    output.h = this->h;

    Vec3 pixel_up = this->u / (this->h/2);
    Vec3 pixel_down = inverse(pixel_up);
    Vec3 pixel_left = this->l / (this->w/2);
    Vec3 pixel_right = inverse(pixel_left);

    Vec3 pixel = this->f + pixel_up*(this->h/2) + pixel_left*(this->w/2); // upper-left pixel
    
    vector<Ray> all;
    for(int i = 0; i<this->w; i++) {
        for(int j = 0; j<this->h; j++) {
            all.push_back(Ray(this->o, pixel + pixel_right*i + pixel_down*j));
        }
    }

    unsigned int i = 0;
    for (Ray r : all) // access by reference to avoid copying
    {
        vector<RGB> row;
        output.p.push_back(row);

        float nearest_distance = INFINITY;
        RGB nearest_rgb = RGB(0,0,0);
        for (int j = 0; j<scene.size(); j++) {

            
            vector<float> distances = scene[j].intersect(r);


            //cout << "DISTANCES: " << distances.size() << endl;
            for (int pene = 0; pene < distances.size(); pene++) {
                //cout << distances[pene] << " ";
            }
            cout << endl;

            
            for (int k = 0; k<distances.size()-1; k++) {
                if(distances[k] < nearest_distance) nearest_rgb = scene[j].emission;
            }
            output.p[i].push_back(nearest_rgb);
        }
        i++;
    }
    return output;
}
