/*
Requirements
=====================
Declareer de volgende klassen:
class Vec3D: Deze class neemt de plaats in van de struct uit de vorige huiswerkopgave. De 
functies uit die opgave, behalve main, zijn nu methods van deze class. De functie die eerst 
vec3D heette, wordt nu de constructor en gaat dus Vec3D heten.
class Ray: Deze class stelt een "lichtstraal" voor. Hij heeft twee fields van het type Vec3D, 
namelijk de steunvector support en de richtingvector direction. Daarnaast heeft hij een 
constructor met de volgende signature:
Ray (float xSup, float ySup, float zSup, float xDir, float yDir, float zDir)
De parameters van de constructor zijn de componenten van respectievelijk support en 
direction.
class Sphere: Deze class stelt een bol voor. Hij heeft fields Vec3D center en float radius. De 
constructor van deze class heeft de signature:
Sphere (float x, float y, float z, float radius)
Daarnaast heeft hij een method die de afstand van z'n center tot een bepaalde Ray berekent, 
met signature:
float distFromRay (Ray const &ray) const
Ook heeft hij een method die bepaalt of een ray de bol raakt, met het prototype:
bool hit (Ray const &ray) const
Tenslotte heeft hij een method die bepaald waar een bepaalde ray de bol raakt, met het 
prototype:

Vec3D hitPoint (Ray const &ray) const
Naast deze classes met hun methods is er de main functie, met het gebruikelijke prototype. In
deze main functie worden een stl::vector gemaakt met daarin volgende bollen:
Sphere (-0.4, 0.23, -1, 0.4), Sphere (0.4, 0.4, -1.2, 0.3) en
Sphere (0.7, -0.15, -1.5, 0.2)
Ook worden een stl::vector gemaakt met daarin de volgende "lichtstralen":
Ray (-far, 0.23, -1, far, 0, 0), Ray (0.4, -far, -1.2, 0, far, 0) en Ray (0.7, -0.15, -far, 0, 0, far)

TestSpecs
=====================
De punten waar de rays de sphere raakt worden in de console uitgeprint
De rays en spheres vectoren komen precies uit in het midden van de bol,
dus zal de distance 0 zijn

Design
=====================
Alles zal in classes en methods staan. De originele functies worden omgezet naar methods
Er wordt gebruik gemaakt van de beschreven classes en methods zoals in de requirements
Voor wiskundige formules wordt gebruik gemaakt van de volgende websites:
https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
https://en.wikipedia.org/wiki/Line–sphere_intersection
*/


#include <iostream>
#include <bits/stdc++.h>
#include <vector>

namespace st = std;

int far = 1000;
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
    protected:
        float x;
        float y;
        float z;
};
Vec3D::Vec3D(float x,float y,float z):
    x (x), y (y), z (z){}

void Vec3D::show(st::string label){
    st::cout << label;
    st::cout << "(" << x <<"  " << y << "  " << z << ")" << '\n';
}
void Vec3D::show(st::string label, float scalar){
    st::cout << label << " ";
    st::cout << scalar << '\n';
}
void Vec3D::show(){
    st::cout<<'\n';
}
Vec3D Vec3D::add (Vec3D const &other){
    float _x= x+other.x;
    float _y= y+other.y;
    float _z= z+other.z;
    return Vec3D{_x,_y,_z};
}
Vec3D Vec3D::sub (Vec3D const &other){
    float _x= this->x-other.x;
    float _y= this->y-other.y;
    float _z= this->z-other.z;
    return Vec3D{_x,_y,_z};
}
Vec3D Vec3D::mul (float scalar){
    float _x= x*scalar;
    float _y= y*scalar;
    float _z= z*scalar;
    return Vec3D{_x,_y,_z};
}
Vec3D Vec3D::minus (){
    return mul(-1);
}
Vec3D Vec3D::div(float scalar){
    float _x= x/scalar;
    float _y= y/scalar;
    float _z= z/scalar;
    return Vec3D{_x,_y,_z};
}
float Vec3D::norm (){
    return sqrt(pow(x,2)+pow(y,2)+pow(z,2)); // length is sqrt of x² + y² + z²
}
Vec3D Vec3D::unit (){
    return div(norm()); //div everything by the length
}
float Vec3D::dot (Vec3D const &other){
    return ((x*other.x)+(y*other.y)+(z*other.z));
}
Vec3D Vec3D::cross (Vec3D const &other){
    float _x = (y*other.z)-(z*other.y);
    float _y = (z*other.x)-(x*other.z);
    float _z = (x*other.y)-(y*other.x);
    return Vec3D{_x,_y,_z};
}

class Ray {
    public:
        Ray(float xSup, float ySup, float zSup, float xDir, float yDir, float zDir);
        Vec3D support; 
        Vec3D direction;        
};
Ray::Ray(float xSup, float ySup, float zSup, float xDir, float yDir, float zDir):
    support(xSup,ySup,zSup), direction(xDir,yDir,zDir){}
class Sphere {
    public:
        Sphere (float x, float y, float z,float radius);
        float distFromRay(Ray &ray);
        bool hit(Ray &ray);
        Vec3D hitpoint(Ray &ray);
        Vec3D center;
    protected:
        float radius;
};
Sphere::Sphere(float x, float y, float z,float radius):
    center(x,y,z),radius(radius){}

float Sphere::distFromRay(Ray &ray){
    return ray.support.sub(center).cross(ray.direction).norm ();
}
bool Sphere::hit(Ray &ray){
    if(distFromRay(ray) <radius){
        ray.support = hitpoint(ray);
        auto normal = ray.support.sub(center).unit();
        auto radial = normal.mul(ray.direction.dot(normal));
        auto tangentail = ray.direction.sub(radial);
        ray.direction = tangentail.sub(radial).unit();
        return true;
    }
    return false;
}
Vec3D Sphere::hitpoint(Ray &ray){
    auto blabla = ray.support.sub(center);
    auto nabla = pow(ray.direction.dot(blabla),2)-pow(blabla.norm(),2)+pow(radius,2);
    auto distFromSupport = -ray.direction.dot(blabla) -sqrt(nabla);
    return ray.support.add (ray.direction.mul(distFromSupport));
}
class Object{
    public:
        Object(float x, float y, float z);
        bool hit(Ray &ray);
        Vec3D center;
};
Object::Object (float x, float y, float z): 
    center (x, y, z) {}

bool Object::hit(Ray &ray){
    
} 



int main(){
    st::vector<Sphere> spheres {Sphere (-0.4, 0.23, -1, 0.4), Sphere (0.4, 0.4, -1.2, 0.3),Sphere(0.7, -0.15, -1.5, 0.2)};
    st::vector<Ray> rays {Ray (-far, 0.23, -1, far, 0, 0), Ray (0.4, -far, -1.2, 0, far, 0), Ray (0.7, -0.15, -far, 0, 0, far)};
    for(auto i = 0;i<spheres.size();i++){
        st::cout << "hit: "<<spheres[i].hit(rays[i])<<'\n';
        st::cout << "disctance: "<<spheres[i].distFromRay(rays[i])<<'\n';
        spheres[i].hitpoint(rays[i]).show("hitpoint: ");
        st::cout << "__________________________"<<'\n';
    }
}