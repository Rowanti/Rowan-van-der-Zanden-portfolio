#include "Classes.hpp"

/*
Requirements
=====================
The program shows 3 floating sphere's above a chessboard patterned floor
Rayscanning must be used to show to sphere's and floor
The image must consist of character, each character denotes a pixel.
extra:
the reflections of other object are shown in the sphere's

TestSpecs
=====================
Test are done visualy.
If the program is run, 3 sphere and a chessboard patterned floor must indeed be visible
If you're close to the creen separate characters must be visible.

Design
=====================
the screen:
    Make a data structure to hold the image.
    The data structure is a vector.
    Each element of that vector is a row of floats on the screen.
    Specifically each row is also a vector of floats, namely a vector of characters.
    Reason: You can compute with float brightness but not with characters.
    (brightness = 1/blackness)
the 3D vector:
    the vector is 3D and must therefor have a x,y,z points and is named Vec3D
    calculation must be done with these vectors
    these calculations are: add,sub,mul,minus,div,norm,unit,dot and cross
Object:
    the object must have a center point which in stored in a Vec3D
    the class must have a visual class hit
the sphere:
    The sphere inherits object
    It has a center and radius
    The function calculates the distance from a ray and whether it hits or not, if so it also calculates where it hits
    when the rays hits it also changes the ray to the reflected ray
the floor:
    the floor has a center and determents if a ray hits a white or black square
    the black square acts like a hole in the floor
    none of the rays reflect
the ray:
    the ray has a support (origin) and a direction
    the ray can scan if he hits any object
the rayscanner:
    the rayscanner "shoots" rays from the eye (support vector) to every point on the screen
    then calls the scan function for every ray it "shoots" and changes the brightness of that pixel
    it can also print the image using the render function
*/

namespace st = std;

int main(){
    auto objects = VPO();
    Sphere *sphere1 = new Sphere(-400, 1800, 150, 100); //medium left sphere
    Sphere *sphere2 = new Sphere(300, 3000, 220, 200);  //big right sphere
    Sphere *sphere3 = new Sphere(-100, 1600, 100, 60);  //small middle sphere
    Floor *vloer = new Floor(0,0,0);                    //floor
    objects.push_back(sphere1);
    objects.push_back(sphere2);
    objects.push_back(sphere3);
    objects.push_back(vloer);
    RayScanner scanner = RayScanner(objects);
    scanner.scan();
    scanner.render();
    return 0;
}