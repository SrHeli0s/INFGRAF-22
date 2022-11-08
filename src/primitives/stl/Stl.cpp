#include "Stl.hpp"
#include "stl_reader.hpp"
#include "../../vec3/Vec3.hpp"
#include "../../point/Point.hpp"
#include "../triangle/Triangle.hpp"
#include "../../tone_mapping/rgb/Rgb.hpp"
#include "../Primitive.hpp"

using namespace std;

STL::STL(const char* path, Point center, float scale, RGB emission)
{
    stl_reader::ReadStlFile(path, coordsSTL, normalsSTL, trisSTL, solidRangesSTL);

    Vec3 translation = center - Point(0,0,0);
    const size_t numTris = trisSTL.size() / 3;
    for(size_t itri = 0; itri < numTris; ++itri) {
        Point p[3];
        for(size_t icorner = 0; icorner < 3; ++icorner) {
            float* c = &coordsSTL[3 * trisSTL[3 * itri + icorner]];
            p[icorner] = Point(c[0]*scale,c[1]*scale,c[2]*scale)+translation;
        }
        tris.push_back(Triangle(p[0],p[1],p[2],emission));
    }
    for (Triangle t:tris) {
        cout << t << endl;
    }
    cout << tris.size() << endl;
}

vector<Collision> STL::intersect(Ray r) {
    vector<Collision> output;
    for (Triangle t: tris) {
        vector<Collision> col = t.intersect(r);
        output.insert( output.end(), col.begin(), col.end() );
    }
    return output;
}
