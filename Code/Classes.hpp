#include <bits/stdc++.h>
#include <vector>
#include "Vector.hpp"

namespace st = std;
class Object;
class Ray;
typedef st::vector<Object*> VPO;
typedef st::vector <float> VF;
typedef st::vector <VF> VVF;

class Ray {
    public:
        Ray(float xSup, float ySup, float zSup, float xDir, float yDir, float zDir);
        Ray(Vec3D &support, Vec3D &direction, VPO &objects);
        Vec3D support;
        Vec3D direction;
        bool scan();
    protected:
        float xStart;
        float yStart;
        VPO objects;
};

class Object{
    public:
        Object(float x, float y, float z);
        virtual bool hit(Ray &ray) = 0;
        Vec3D center;
};

class Sphere : public Object {
    public:
        Sphere (float x, float y, float z,float radius);
        float distFromRay(Ray &ray);
        bool hit(Ray &ray);
        Vec3D hitpoint(Ray &ray) const;
    protected:
        float radius;
};
class Floor: public Object {
    public:
        Floor (float x, float y, float z);
        bool hit(Ray &ray);
};
class RayScanner {
    public:
        RayScanner (VPO &objects);
        void scan();
        void render();
        VPO objects;
        int const nrOfRows = 300;
        int const nrOfCols = 600;
        char const *pixelCharts = "MI. ";
        float const black = sizeof(pixelCharts)/ sizeof(char)-1;
        VVF image = VVF (nrOfRows, VF (nrOfCols, black));

};