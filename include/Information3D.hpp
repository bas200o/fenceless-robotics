/*Class used to keep track of 3d info*/
#pragma once
#include "../include/FoundObject.hpp"
#include <vector>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>

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



