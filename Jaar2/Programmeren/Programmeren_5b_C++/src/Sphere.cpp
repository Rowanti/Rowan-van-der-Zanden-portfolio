#include "Classes.hpp"

namespace st = std;

Sphere::Sphere(float x, float y, float z,float radius):
    Object(x,y,z), radius(radius){}

float Sphere::distFromRay(Ray &ray){
    return ray.support.sub(center).cross(ray.direction).norm();
}
bool Sphere::hit(Ray &ray){
    // check if the origin of the vector is in the sphere.
    // this may if the origin is in the sphere it may hit the sphere itself when reflecting
    if(ray.support.x>center.x-radius/2 && ray.support.x<center.x+radius/2){
        return 0;
    } else if(ray.support.y>center.y-radius/2 && ray.support.y<center.y+radius/2){
        return 0;
    } else if(ray.support.z>center.z-radius/2 && ray.support.z<center.z+radius/2){
        return 0;
    }
    if(distFromRay(ray) <radius){
        ray.support = hitpoint(ray);    //new support vector
        auto normal = ray.support.sub(center).unit();
        auto radial = normal.mul(ray.direction.dot(normal));
        auto tangentail = ray.direction.sub(radial);
        ray.direction = tangentail.sub(radial).unit();  //new direction vector
        return true;
    }
    return false;
}
Vec3D Sphere::hitpoint(Ray &ray) const{
    auto blabla = ray.support.sub(center);
    auto nabla = pow(ray.direction.dot(blabla),2)-pow(blabla.norm(),2)+pow(radius,2);
    auto distFromSupport = -ray.direction.dot(blabla) -sqrt(nabla);
    return ray.support.add (ray.direction.mul(distFromSupport));
}