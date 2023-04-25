#include "Classes.hpp"

namespace st = std;

Ray::Ray(float xSup, float ySup, float zSup, float xDir, float yDir, float zDir):
    support(xSup,ySup,zSup), direction(xDir,yDir,zDir){}

Ray::Ray(Vec3D &support, Vec3D &direction, VPO &objects):
    support(support), direction(direction.unit()), objects(objects){}

bool Ray::scan(){
    for(auto x:objects){
        if(x->hit(*this)){
            return 1;
        }
    }
    return 0;
}
