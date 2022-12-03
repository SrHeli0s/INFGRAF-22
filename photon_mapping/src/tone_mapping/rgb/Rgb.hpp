#pragma once
#include <iostream>
#include <vector>

class RGB {
    public:
        float r,g,b;
        
    RGB();
    RGB(float r,float g,float b);

    float maxChannel();

    const RGB operator+ (float f) const;
    const RGB operator+ (RGB f) const;
    const RGB operator- (float f) const;
    const RGB operator- (RGB f) const;
    const RGB operator/ (float f) const;
    const RGB operator/ (RGB f) const;
    const RGB operator* (float f) const;
    const RGB operator* (RGB f) const;
    const bool operator== (RGB f) const;
    const bool operator!= (RGB f) const;
};

std::ostream& operator << (std::ostream& os, const RGB& obj);
