#include "../include/FoundObject.hpp"

FoundObject::FoundObject(pcl::PointCloud<pcl::PointXYZRGB> objectCloud)
{
    this->objectCloud = objectCloud;
    //calculate values
    CalculateValues();
    //CalculateSize();
}
FoundObject::FoundObject()
{
}

FoundObject::~FoundObject()
{
}

/**
 * Calculate statistical values of objects
 * @return void saves data to object
 */
void FoundObject::CalculateValues()
{
    float x = 0, y = 0, z = 0;
    float ly, lx, hy, hx, maxsize = 0;
    int numPoints = objectCloud.size();
    for (int i = 0; i < numPoints; i++)
    {
        x += objectCloud.points[i].x;
        y += objectCloud.points[i].y;
        z += objectCloud.points[i].z;
    }
    float cx, cy, cz, cx2, cy2, cz2;
    cx = x / numPoints;
    cy = y / numPoints;
    cz = z / numPoints;
    location.x = cx;
    location.y = cy;
    location.z = cz;

    centerMass = std::tuple<float, float, float>{cx, cy, cz};
    cout<< std::get<0>(centerMass) << endl;
    cout<< std::get<1>(centerMass) << endl;
    cout<< std::get<2>(centerMass) << endl;
    for (int i = 0; i < numPoints; i++)
    {
        //Can possibly result in inaccuracies, use location instead of objectCloud.points[0] for the right values
        float tempsize = euclideanDistance(objectCloud.points[i], objectCloud.points[0]);
        tempsize = abs(tempsize);
        if (tempsize > maxsize)
        {
            maxsize = tempsize;
        }
    }
    size = maxsize;
}

void FoundObject::setSpeed(double sp)
{
    // std::cout << sp << std::endl;
    speed = sp;
}

double FoundObject::getSpeed()
{
    return FoundObject::speed;
}

pcl::PointCloud<pcl::PointXYZRGB> FoundObject::getObjectCloud()
{
    return FoundObject::objectCloud;
}

pcl::PointXYZRGB FoundObject::getLocation()
{
    return FoundObject::location;
}

float FoundObject::getSize()
{
    return FoundObject::size;
}

std::tuple<float, float, float> FoundObject::getCenterMass()
{
    return FoundObject::centerMass;
};


    void FoundObject::setIdentificationNumber(int number){
        FoundObject::identificationNumber = number;
    }

    int FoundObject::getIdentificationNumber(){
        return(FoundObject::identificationNumber);
    }

    float FoundObject::getDirectionVer(){
        return FoundObject::directionVer;
    }

    float FoundObject::getDirectionHor(){
        return FoundObject::directionHor;
    }

    void FoundObject::setDirectionHor(float x){
        
        FoundObject::directionHor = x;
    }

    void FoundObject::setDirectionVer(float y){
        
        FoundObject::directionVer = y;
    }

    void FoundObject::setDirection(double idk){
        FoundObject::direction = idk;
    }
