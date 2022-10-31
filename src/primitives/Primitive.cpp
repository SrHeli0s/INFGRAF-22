#include "Primitive.hpp"

using namespace std;

ostream& operator << (ostream& os, const Primitive& p) {
    os << p.to_string();
    return os;
};