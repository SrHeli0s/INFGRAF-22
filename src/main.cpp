#include "point/Point.hpp"
#include "vec3/Vec3.hpp"
#include "transformation/Transformation.hpp"
#include "sphere/Sphere.hpp"
#include <iostream>
using namespace std;

int main() {

    Point p1 = Point(1,0,0);
    Point p2 = Point(1,1,0);
    Vec3 v1 = Vec3(2,1,1);
    Transformation t = ScaleTransform(1,2,1);
    v1.applyTransformation(t);

    cout << v1 << " " << p2 <<  "\n" << t << "\n" << t.inverse() << "\n" << endl;

    Sphere s = Sphere(Point(3,3,3),Vec3(0,2,2),Point(4,4,3));

    cout << s.surfacePoint(M_PI/2, 0) << " " << mod(s.center-s.surfacePoint(M_PI/2, 0)) << " " << s.surfacePoint(M_PI/2, M_PI/2) << "\n" << endl;

    return 0;
}