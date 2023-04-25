#include "Classes.hpp"

Floor::Floor(float x, float y, float z):
    Object(x,y,z){}

bool Floor::hit(Ray &ray){
    float lenght = (0-ray.support.z / ray.direction.z);
    if(lenght>0){
    Vec3D scaledVector = ray.support.add(ray.direction.mul(lenght));
        if ((int)(floor(scaledVector.x / 10) + floor(scaledVector.y / 10)) % 2 == 0){ //if its a white square return 1
            return 1;   
        }  
    }
    return 0;
}