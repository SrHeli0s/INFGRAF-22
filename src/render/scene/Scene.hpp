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

class Scene {
    public:
        Camera cam;
        vector<shared_ptr<Primitive>> objs;
        vector<PointLight> lights;

    Scene();

    void addP(const shared_ptr<Primitive> p);
    void addP(Sphere p);
    void addP(Plane p);
    void addP(Triangle p);
    void addP(STL p);
    void addL(PointLight p);
};