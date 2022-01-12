#include "../include/FoundObject.hpp"


FoundObject::FoundObject(pcl::PointCloud<pcl::PointXYZRGB> objectCloud)
{
    this->objectCloud = objectCloud;
    //calculate values
    CalculateCenterMass();
    CalculateSize();
}

FoundObject::~FoundObject()
{
}

void FoundObject::CalculateCenterMass(){
float x = 0, y = 0;
float ly, lx, hy, hx;
int numPoints = objectCloud.size();
for(int i = 0 ; i < numPoints ; i++){
    //pcl::PointCloud<pcl::
    x += objectCloud.points[i].x;
    y += objectCloud.points[i].y;
    //object
    //if(ly < objectCloud.point[i].fgs
}
float cx, cy;
cx = x/numPoints;
cy = y/numPoints;
centerMass = std::tuple<float, float> {cx, cy};
location = std::tuple<float, float> {cx, cy};
return;
}

void FoundObject::CalculateLocation(){

}

void FoundObject::CalculateSize(){

}
