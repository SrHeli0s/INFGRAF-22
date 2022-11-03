#pragma once

#include <vector>
#include <memory>
#include "../camera/Camera.hpp"

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

    Scene();

    void add(const shared_ptr<Primitive> p);
    void add(Sphere p);
    void add(Plane p);
    void add(Triangle p);
};