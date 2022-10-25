#include "utils.hpp"
#include <cmath>

SecondDegreeEquationSolution solveSecondDegreeEquation(float a, float b, float c)
{
  SecondDegreeEquationSolution result={0};

  if(a<0.000001)    // ==0
  {
    if(b>0.000001) { // !=0
      result.p1 = result.p2 = -c/b;
      result.nSols = 1;
    } else if(c>0.00001) result.nSols = 0;
    return result;
  }

  double delta=b*b-4*a*c;
  if(delta>=0)
  {
    result.p1 = (-b-sqrt(delta))/2/a;
    result.p2 = (-b+sqrt(delta))/2/a;
    result.nSols = 2;
  }
  else
    result.nSols = 0;

  return result;
}