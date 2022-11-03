#include "Camera.hpp"
#include "../../point/Point.hpp"
#include "../../vec3/Vec3.hpp"
#include "../../primitives/Primitive.hpp"
#include "../../primitives/sphere/Sphere.hpp"
#include "../../primitives/plane/Plane.hpp"
#include "../../tone_mapping/image/Image.hpp"
#include "../../utils/Utils.hpp"
#include "../ray/Ray.hpp"
#include "../scene/Scene.hpp"
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

ostream& operator << (ostream& os, const Camera& obj)
{
    os << "Camera(origin=" << obj.o << ", up=" << obj.u << ", left=" << obj.l
    << ", foward=" << obj.f << ", wxh=" << obj.w << "x" << obj.h << ")";
    return os;
}

Image Camera::render(Scene scene, unsigned int nRays = 1)
{
    Image output;
    output.w = this->w;
    output.h = this->h;
    output.color_res = 255;

    Vec3 pixel_up = this->u / (this->h/2);
    Vec3 pixel_down = inverse(pixel_up);
    Vec3 pixel_left = this->l / (this->w/2);
    Vec3 pixel_right = inverse(pixel_left);

    Vec3 pixel = this->f + this->l + this->u; // upper-left pixel

    //Prepare output.p
    for(int i = 0; i<this->h; i++) {
        vector<RGB> row;
        output.p.push_back(row);
    }
    
    //Iterate
    for(int i = 0; i<this->h; i++) {
        for(int j = 0; j<this->w; j++) {
            vector<RGB> colors;
            
            for (int y = 0; y<nRays; y++) {

                Ray rayo = Ray(this->o, pixel + pixel_right*(j+(rand()/(float) (RAND_MAX))) + pixel_down*(i+(rand()/(float) (RAND_MAX))));
                float nearest_distance = INFINITY;
                RGB nearest_rgb = RGB(0,0,0);
                shared_ptr<Primitive> nearest_obj;
                for (int x = 0; x<scene.objs.size(); x++) {
                    vector<float> distances = scene.objs[x]->intersect(rayo);
                    for (int k = 0; k < distances.size(); k++) {
                        if(distances[k] < nearest_distance) {
                            nearest_rgb = scene.objs[x]->emission;
                            nearest_distance = distances[k];
                            nearest_obj = scene.objs[x];
                        }
                    }
                }

                Point hit = rayo.p + (rayo.v * nearest_distance);
                RGB sum = RGB(0,0,0);
                //P4
                for (auto l: scene.lights) {
                    sum = sum + (l.power)/(float)(pow(mod(l.center - hit),2));
                    float x = ((l.center-hit)/(mod(l.center - hit)));
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

            output.p[i].push_back(average_rgb);
            //Set output.maxvalue to the max of average_rgb.r, average_rgb.g, average_rgb.b and output.maxvalue
            output.max_value = (average_rgb.r>output.max_value) ? average_rgb.r : ((average_rgb.g>output.max_value) ? average_rgb.g : ((average_rgb.b>output.max_value) ? average_rgb.b : output.max_value));
        }
    }

    return output;
}
