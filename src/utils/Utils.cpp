#include "Utils.hpp"
#include <cmath>
#include <vector>

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