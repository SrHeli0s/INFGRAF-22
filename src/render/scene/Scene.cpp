#include "Scene.hpp"
#include "../../primitives/Primitive.hpp"
#include "../../primitives/sphere/Sphere.hpp"
#include "../../primitives/plane/Plane.hpp"
#include "../../primitives/triangle/Triangle.hpp"
#include "../light/light_source/PLSource.hpp"

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

void Scene::addL(PLSource p){
    // lights.push_back(p);    
}