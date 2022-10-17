#pragma once
#include <iostream>
#include <vector>

class RGB {
    public:
        float r,g,b;
        
    RGB();
    RGB(float r,float g,float b);
};

std::ostream& operator << (std::ostream& os, const RGB& p);
