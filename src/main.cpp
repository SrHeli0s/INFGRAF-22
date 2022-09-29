#include "Point.hpp"
#include "Vec3.hpp"
#include "Transformation.hpp"
#include <iostream>
using namespace std;

int main() {

    Point p1 = Point(1,0,0);
    Point p2 = Point(1,1,0);
    Vec3 v1 = Vec3(2,1,1);
    Transformation t = ScaleTransform(1,2,1);
    v1.applyTransformation(t);


    cout << v1 << " " << p2 <<  " " << t << endl;

    return 0;
}