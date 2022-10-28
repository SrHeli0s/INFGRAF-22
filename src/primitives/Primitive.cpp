#include "Primitive.hpp"

using namespace std;

ostream& operator << (ostream& os, const Primitive& p) {
    os << p.printear();
    return os;
};