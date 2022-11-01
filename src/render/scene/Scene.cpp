#include "Scene.hpp"
#include "../../primitives/Primitive.hpp"
#include "../../primitives/sphere/Sphere.hpp"
#include "../../primitives/plane/Plane.hpp"

Scene::Scene() {}


void Scene::add(const shared_ptr<Primitive> p){
    objs.push_back(p);    
}

void Scene::add(Sphere p){
    objs.push_back(make_shared<Sphere>(p));    
}

void Scene::add(Plane p){
    objs.push_back(make_shared<Plane>(p));    
}