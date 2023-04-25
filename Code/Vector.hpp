#include <bits/stdc++.h>
#include <vector>
namespace st = std;

class Vec3D {
    public:
        Vec3D(float x,float y,float z);
        void show(st::string label);
        void show(st::string label, float scalar);
        void show();
        Vec3D add(Vec3D const &other);
        Vec3D sub(Vec3D const &other);
        Vec3D mul(float scalar);
        Vec3D minus();
        Vec3D div(float scalar);
        float norm();
        Vec3D unit();
        float dot(Vec3D const &other);
        Vec3D cross(Vec3D const &other);
        float x;
        float y;
        float z;
};