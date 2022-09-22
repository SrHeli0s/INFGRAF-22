#include "Point.cpp"
#include "Vec3.cpp"
#include <iostream>
using namespace std;

int main() {

    Point p1 = Point(1,0,0);
    Point p2 = Point(1,1,0);
    Vec3 v1 = Vec3(2,0,0);



    cout << p1-p2 << " " << v1+p1 << endl;

    return 0;
}