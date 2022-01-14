#include "../include/FoundObject.hpp"

FoundObject::FoundObject(pcl::PointCloud<pcl::PointXYZRGB> objectCloud)
{
    this->objectCloud = objectCloud;
    //calculate values
    CalculateValues();
    //CalculateSize();
}
FoundObject::FoundObject(){

}

FoundObject::~FoundObject()
{
}

void FoundObject::CalculateValues(){
float x = 0, y = 0, z = 0;
float ly, lx, hy, hx, maxsize = 0;
int numPoints = objectCloud.size();
for(int i = 0 ; i < numPoints ; i++){
    //pcl::PointCloud<pcl::
    x += objectCloud.points[i].x;
    y += objectCloud.points[i].y;
    z += objectCloud.points[i].z;
    //object
    //if(ly < objectCloud.points[i].
}
float cx, cy, cz;
cx = x/numPoints;
cy = y/numPoints;
cz = z/numPoints;
location = pcl::PointXYZRGB(cx, cy, cz);
centerMass = std::tuple<float, float, float> {cx, cy, cz};

    for (int i = 0; i < numPoints; i++)
    {
        float tempsize = euclideanDistance(objectCloud.points[i], objectCloud.points[0]);
        if (tempsize < 0)
        {
            tempsize = tempsize * -1;
        }
        if (tempsize > maxsize)
        {
            maxsize = tempsize;
        }
    }
size = maxsize;
return;
}

    void FoundObject::setSpeed(float sp){
        FoundObject::speed = sp;
    }

    float FoundObject::getSpeed(){
        return FoundObject::speed;
    }

    pcl::PointCloud<pcl::PointXYZRGB> FoundObject::getObjectCloud(){
        return FoundObject::objectCloud;
    }
    
    pcl::PointXYZRGB FoundObject::getLocation(){
        return FoundObject::location;
    }

    float FoundObject::getSize(){
        return FoundObject::size;
    }