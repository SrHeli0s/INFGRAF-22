#pragma once
#include <iostream>
#include <vector>

class RGB {
    public:
        float r,g,b;
        
    RGB();
    RGB(float r,float g,float b);

    const RGB operator+ (float f) const;
    const RGB operator+ (RGB f) const;
    const RGB operator- (float f) const;
    const RGB operator/ (float f) const;
    const RGB operator* (float f) const;
    
};

std::ostream& operator << (std::ostream& os, const RGB& obj);
