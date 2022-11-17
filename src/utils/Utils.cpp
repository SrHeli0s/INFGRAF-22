#include "Utils.hpp"
#include <cmath>
#include <vector>
#include <utility>
#include <memory>
#include "../render/ray/Ray.hpp"
#include "../render/scene/Scene.hpp"
#include "../primitives/Primitive.hpp"

using namespace std;

vector<float> solveSecondDegreeEquation(float a, float b, float c)
{
  vector<float> output;

  if(a<0.000001)    // ==0
  {
    if(b>0.000001 && b<-0.000001) { // !=0
      output.push_back(-c/b);
    } 
    return output;
  }

  double delta=b*b-4*a*c;
  if(delta>0)
  {
    output.push_back((-b-sqrt(delta))/2/a);
    output.push_back((-b+sqrt(delta))/2/a);
  }
  else if (delta == 0) {
    output.push_back((-b-sqrt(delta))/2/a);
  }

  return output;
}

bool isfZero(float a) {
  return abs(a)<ZERO_THRESHOLD;
}

Collision closest_col(Ray r, Scene s) {
  Collision output = {nullptr,Point(0,0,0),Vec3(0,0,0),r,INFINITY};
  for (int x = 0; x<s.objs.size(); x++) {
    vector<Collision> collisions = s.objs[x]->intersect(r);
    for (int k = 0; k < collisions.size(); k++) {
      if(collisions[k].distance < output.distance && !isfZero(collisions[k].distance)) output = collisions[k];
    }
  }

  return output;
}