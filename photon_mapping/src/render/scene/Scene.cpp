#include "Scene.hpp"
#include "../../primitives/Primitive.hpp"
#include "../../primitives/sphere/Sphere.hpp"
#include "../../primitives/plane/Plane.hpp"
#include "../../primitives/triangle/Triangle.hpp"
#include "../../primitives/stl/Stl.hpp"
#include "../../primitives/sprite/Sprite.hpp"
#include "../light/point_light/PointLight.hpp"

Scene::Scene() {}


void Scene::addP(const shared_ptr<Primitive> p){
    objs.push_back(p);
}

void Scene::addP(Sphere p){
    objs.push_back(make_shared<Sphere>(p));
}

void Scene::addP(Plane p){
    objs.push_back(make_shared<Plane>(p));
}

void Scene::addP(Triangle p){
    objs.push_back(make_shared<Triangle>(p));
}

void Scene::addP(STL p){
    objs.push_back(make_shared<STL>(p));
}

void Scene::addP(Sprite p){
    objs.push_back(make_shared<Sprite>(p));
}

void Scene::addL(PointLight p){
    lights.push_back(p);    
}

void Scene::addL(const shared_ptr<Primitive> p) {
    area_lights.push_back(p);
}

void Scene::addL(Sphere p){
    area_lights.push_back(make_shared<Sphere>(p));
}

void Scene::addL(Plane p){
    area_lights.push_back(make_shared<Plane>(p));
}

void Scene::addL(Triangle p){
    area_lights.push_back(make_shared<Triangle>(p));
}

void Scene::addL(STL p){
    area_lights.push_back(make_shared<STL>(p));
}

void Scene::addL(Sprite p){
    area_lights.push_back(make_shared<Sprite>(p));
}