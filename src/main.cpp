#include "Point.hpp"
#include "Vec3.hpp"
#include "Transformation.hpp"
#include <iostream>
using namespace std;

int main() {

    Point p1 = Point(1,0,0);
    Point p2 = Point(1,1,0);
    Vec3 v1 = Vec3(2,0,0);
    Transformation t = ScaleTransform(1,2,1);


    cout << t << " " << v1+p1 << endl;

    return 0;
}