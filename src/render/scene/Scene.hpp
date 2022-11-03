#pragma once

#include <vector>
#include <memory>
#include "../camera/Camera.hpp"
#include "../light/light_source/PLSource.hpp"

using namespace std;

class Image;
class Primitive;
class Sphere;
class Plane;
class Triangle;

class Scene {
    public:
        Camera cam;
        vector<shared_ptr<Primitive>> objs;
        vector<PLSource> lights;

    Scene();

    void addP(const shared_ptr<Primitive> p);
    void addP(Sphere p);
    void addP(Plane p);
    void addP(Triangle p);
    void addL(PLSource p);
};