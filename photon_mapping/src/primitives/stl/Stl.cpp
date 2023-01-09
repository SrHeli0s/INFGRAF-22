#include "Stl.hpp"
#include "stl_reader.hpp"
#include "../../vec3/Vec3.hpp"
#include "../../point/Point.hpp"
#include "../triangle/Triangle.hpp"
#include "../../tone_mapping/rgb/Rgb.hpp"
#include "../Primitive.hpp"
#include "../../utils/Utils.hpp"

using namespace std;

STL::STL(const char* path, Point center, float scale, Material material)
{
    stl_reader::ReadStlFile(path, coordsSTL, normalsSTL, trisSTL, solidRangesSTL);

    Point maxPoint = Point(-INFINITY,-INFINITY,-INFINITY);
    Point minPoint = Point(INFINITY,INFINITY,INFINITY);

    Vec3 translation = center - Point(0,0,0);
    const size_t numTris = trisSTL.size() / 3;
    for(size_t itri = 0; itri < numTris; ++itri) {
        Point p[3];
        for(size_t icorner = 0; icorner < 3; ++icorner) {
            float* c = &coordsSTL[3 * trisSTL[3 * itri + icorner]];
            p[icorner] = Point(c[0]*scale,c[1]*scale,c[2]*scale)+translation;
            
            float value = (p[icorner].c[0]+p[icorner].c[1]+p[icorner].c[2]);
            if (value > (maxPoint.c[0]+maxPoint.c[1]+maxPoint.c[2])) maxPoint = p[icorner];
            if (value < (minPoint.c[0]+minPoint.c[1]+minPoint.c[2])) minPoint = p[icorner];
        }
        tris.push_back(Triangle(p[0],p[1],p[2],material));
    }

    center = Point((maxPoint.c[0]+minPoint.c[0])/2,(maxPoint.c[1]+minPoint.c[1])/2,(maxPoint.c[2]+minPoint.c[2])/2);
}

vector<Collision> STL::intersect(Ray r) {
    vector<Collision> output;
    for (Triangle t: tris) {
        vector<Collision> col = t.intersect(r);
        output.insert( output.end(), col.begin(), col.end() );
    }
    return output;
}

Point STL::getRandomPoint(Scene sc) {
    float randInclination = acos(2*(rand()/(float) (RAND_MAX)) - 1);
    float randAzimuth = 2*M_PI*(rand()/(float) (RAND_MAX));

    Vec3 dir = Vec3(sin(randInclination) * cos(randAzimuth),
                    sin(randInclination) * sin(randAzimuth),
                    cos(randInclination));
    
    Ray r = Ray(center, dir);

    Collision c = closest_col(r,sc);

    return c.collision_point;
}