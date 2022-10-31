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

ostream& operator << (ostream& os, const Camera& obj)
{
    os << "Camera(origin=" << obj.o << ", up=" << obj.u << ", left=" << obj.l
    << ", foward=" << obj.f << ", wxh=" << obj.w << "x" << obj.h << ")";
    return os;
}

Image Camera::render(Primitive* scene[], unsigned int size)
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
            Ray rayo = Ray(this->o, pixel + pixel_right*j + pixel_down*(this->h-i-1));

            float nearest_distance = INFINITY;
            RGB nearest_rgb = RGB(0,0,0);
            for (int x = 0; x<size; x++) {
                vector<float> distances = scene[x]->intersect(rayo);
                for (int k = 0; k < distances.size(); k++) {
                    if(distances[k] < nearest_distance) {
                        nearest_rgb = scene[x]->emission;
                        nearest_distance = distances[k];
                    }
                }
            }
            output.p[i].push_back(nearest_rgb);
            //Set output.maxvalue to the max of nearest_rgb.r, nearest_rgb.g, nearest_rgb.b and output.maxvalue
            output.max_value = (nearest_rgb.r>output.max_value) ? nearest_rgb.r : ((nearest_rgb.g>output.max_value) ? nearest_rgb.g : ((nearest_rgb.b>output.max_value) ? nearest_rgb.b : output.max_value));

        }
    }

    return output;
}
