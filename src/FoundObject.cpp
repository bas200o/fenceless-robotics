#include "../include/FoundObject.hpp"


FoundObject::FoundObject(pcl::PointCloud<pcl::PointXYZRGB> objectCloud)
{
    this->objectCloud = objectCloud;
    //calculate values
}

FoundObject::~FoundObject()
{
}