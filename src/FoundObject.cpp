#include "../include/FoundObject.hpp"

FoundObject::FoundObject(pcl::PointCloud<pcl::PointXYZRGB> objectCloud)
{
    this->objectCloud = objectCloud;
    //calculate values
    CalculateValues();
    //CalculateSize();
}

FoundObject::~FoundObject()
{
}

void FoundObject::CalculateValues()
{
    float x = 0, y = 0;
    float ly, lx, hy, hx, maxsize = 0;
    int numPoints = objectCloud.size();
    for (int i = 0; i < numPoints; i++)
    {
        //pcl::PointCloud<pcl::
        x += objectCloud.points[i].x;
        y += objectCloud.points[i].y;
        //object
        //if(ly < objectCloud.points[i].
    }
    float cx, cy;
    cx = x / numPoints;
    cy = y / numPoints;
    centerMass = std::tuple<float, float>{cx, cy};
    location = std::tuple<float, float>{cx, cy};

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