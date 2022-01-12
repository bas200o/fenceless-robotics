/*Objects found in 3d pcl*/
#pragma once
#include <tuple>
#include <vector>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>

class FoundObject
{
private:
    std::tuple<float, float> location;
    std::tuple<float, float> size;//misschien los width height depth
    std::tuple<float, float> centerMass;
    pcl::PointCloud<pcl::PointXYZRGB> objectCloud;
    void CalculateCenterMass();
    void CalculateSize();
    void CalculateLocation();

public:
    FoundObject(pcl::PointCloud<pcl::PointXYZRGB> objectCloud);
    ~FoundObject();
};

