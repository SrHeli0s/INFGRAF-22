#include "Sprite.hpp"
#include "../../tone_mapping/ppm/PPM.hpp"
#include "../../utils/Utils.hpp"
#include "../../render/ray/Ray.hpp"
#include <cmath>
#include <vector>

using namespace std;

Sprite::Sprite(Point center, Vec3 normal, Vec3 up, const char* path, float scale) {
    float x = center.c[0]*normal.c[0] + center.c[1]*normal.c[1] + center.c[2]*normal.c[2];
    this->c = x / mod(normal);
    this->center = center;
    this->normal = normal;
    this->material = Material();
    PPM reader = PPM();
    this->img = reader.read(path);
    this->a = normalize(up);
    this->b = normalize(cross(normal,up));
    this->scale = scale;
    this->transparent = RGB(-1,-1,-1); //Imposible color
}

Sprite::Sprite(Point center, Vec3 normal, Vec3 up, const char* path, float scale, RGB transparent_color) {
    float x = center.c[0]*normal.c[0] + center.c[1]*normal.c[1] + center.c[2]*normal.c[2];
    this->c = x / mod(normal);
    this->center = center;
    this->normal = normal;
    this->material = Material();
    PPM reader = PPM();
    this->img = reader.read(path);
    this->a = normalize(up);
    this->b = normalize(cross(normal,up));
    this->scale = scale;
    this->transparent = transparent_color;
}

bool Sprite::insideSprite(Point p) {
    //https://stackoverflow.com/questions/23472048/projecting-3d-points-to-2d-plane
    int x = a * (p-center) * scale;
    int y = b * (p-center) * scale;

    if (x>0 && y>0 && img.w>x && img.h>y) {
        if (img.p[x][y] == transparent) return false;
        return true;
    }
    return false;
}

RGB Sprite::getEmission(Point p) {
    int x = a * (p-center) * scale;
    int y = b * (p-center) * scale;
    if (insideSprite(p)) return img.p[x][img.h-y];
    else return material.dif;
};

vector<Collision> Sprite::intersect(Ray r) {
    vector<Collision> output;
    if(r.v*this->normal == 0) return output;

    float distance = -(this->c + this->normal*r.p)/(r.v*this->normal);
    if(distance<0) return output; //The plane is behind the ray
    
    Point contact = r.p+(r.v*distance);
    //TODO: Is this transparency check correct?
    if (distance>MIN_DISTANCE && insideSprite(contact) && (getEmission(contact)*(img.max_value/img.color_res))!=transparent)
        output.push_back({
            make_shared<Sprite>(*this),
            contact,
            this->normal,
            r,
            distance
        });
    
    return output;
}