#pragma once
#include <iostream>
#include "../point/Point.hpp"
#include "../tone_mapping/rgb/Rgb.hpp"

using namespace std;

class Photon {
    public :
        Point p;
        RGB flux;

    Photon();
    Photon(Point p, RGB flux);
};

std::ostream& operator << (std::ostream& os, const Photon& obj);

struct PhotonAxisPosition {
    float operator()(const Photon& p, std::size_t i) const {
        return p.p.c[i];
    }
};