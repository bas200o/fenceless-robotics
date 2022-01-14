/*Objects found in 3d pcl*/
#pragma once
#include <tuple>
#include <vector>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/common/distances.h>

class FoundObject
{
private:
    pcl::PointXYZRGB location;
    //std::tuple<float, float> size;//misschien los width height depth
    float size;
    float speed;
    std::tuple<float, float, float> centerMass;
    pcl::PointCloud<pcl::PointXYZRGB> objectCloud;
    void CalculateValues();
    void CalculateSize();
    void CalculateLocation();


public:
    FoundObject(pcl::PointCloud<pcl::PointXYZRGB> objectCloud);
    FoundObject();
    ~FoundObject();
    void setSpeed(float sp);
    float getSpeed();
    pcl::PointCloud<pcl::PointXYZRGB> getObjectCloud();
    pcl::PointXYZRGB getLocation();
    float getSize();

};

