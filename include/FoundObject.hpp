/*Objects class for found objects in pointcloud*/
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
    //Point with the location/centermass of the FoundObject
    pcl::PointXYZRGB location;
    //The longest size of an object
    float size = 0;
    double speed = -1;
    //The centermass of the object
    std::tuple<float, float, float> centerMass;
    //The pointcloud of the object
    pcl::PointCloud<pcl::PointXYZRGB> objectCloud;
    //Calculates the size and location of the object
    void CalculateValues();


public:
    //Constructor
    FoundObject(pcl::PointCloud<pcl::PointXYZRGB> objectCloud);
    FoundObject();
    //Destructor
    ~FoundObject();
    void setSpeed(double sp);
    double getSpeed();
    pcl::PointCloud<pcl::PointXYZRGB> getObjectCloud();
    pcl::PointXYZRGB getLocation();
    std::tuple<float, float, float> getCenterMass();
    float getSize();

};
