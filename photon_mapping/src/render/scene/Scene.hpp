#pragma once

#include <vector>
#include <memory>
#include "../camera/Camera.hpp"
#include "../light/point_light/PointLight.hpp"

using namespace std;

class Image;
class Primitive;
class Sphere;
class Plane;
class Triangle;
class STL;
class Sprite;

class Scene {
    public:
        Camera cam;
        vector<shared_ptr<Primitive>> objs;
        vector<PointLight> lights;
        vector<shared_ptr<Primitive>> area_lights;

    Scene();

    void addP(const shared_ptr<Primitive> p);
    void addP(Sphere p);
    void addP(Plane p);
    void addP(Triangle p);
    void addP(STL p);
    void addP(Sprite p);
    void addL(PointLight p);
    void addL(const shared_ptr<Primitive> p);
    void addL(Sphere p);
    void addL(Plane p);
    void addL(Triangle p);
    void addL(STL p);
    void addL(Sprite p);
};