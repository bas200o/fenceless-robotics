#pragma once
#include "../include/FoundObject.hpp"

class Information3D
{
private:
    std::vector<FoundObject> objects;
    std::vector<pcl::PointCloud<pcl::PointXYZRGB>> indiviualPointClouds;
    pcl::PointCloud<pcl::PointXYZRGB> fullPointCloud;
    
    
public:
    Information3D(/* args */);
    ~Information3D();
};



