#pragma once
#include <cmath>
#include <iostream>
#include "../../vec3/Vec3.hpp"


class Plane {
    public:
        Vec3 x,y;
        
    Plane();
    Plane(Vec3 x, Vec3 y);

};