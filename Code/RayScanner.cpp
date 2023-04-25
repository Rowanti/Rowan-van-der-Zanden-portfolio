#include <iostream>
#include "Classes.hpp"

RayScanner::RayScanner(VPO &objects):
    objects (objects){}

void RayScanner::scan(){
    for(auto i=0;i<nrOfRows;i++){
        for(auto j=0;j<nrOfCols;j++){
            Vec3D endPoint = Vec3D(-(nrOfCols / 2) + j, 0, (nrOfRows / 2) - i); //point on the screen
            Vec3D support = Vec3D(0, -1500, 10);        //support = eye
            Vec3D direction = endPoint.sub(support);
            Ray startPoint = Ray(support, direction, objects);
            Ray tempRay = startPoint;       //temporary ray
            auto bestHit = startPoint.scan() ?2:1;
            int reflection = 1;
            if(tempRay.direction.x!=startPoint.direction.x){    //checks if the direction of the vector has changed
                reflection = startPoint.scan() ?2:1;
            }
            //devides brightness by a number to make the image brighter when an object has been hit
            image [i][j]/=(bestHit*reflection);
        }
    }
}
void RayScanner::render(){
    st::cout <<'\n';
    for(auto rowIndex = 0; rowIndex < nrOfRows; rowIndex++){
        st::cout <<"                              ";
        for(auto colIndex = 0;colIndex<nrOfCols; colIndex++){
            for(auto i=0;i<3;i++){
                st::cout << pixelCharts [int (image [rowIndex][colIndex])]; //prints char depending on the brightness
            }
        }
        st::cout <<'\n';
    }
}