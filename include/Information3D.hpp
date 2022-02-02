#pragma once
#include "../include/FoundObject.hpp"
#include <vector>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>

/**
 * Class keeps information abouth 3d objects.
 */
class Information3D
{
private:

    //Vector of individual pointclouds
    std::vector<pcl::PointCloud<pcl::PointXYZRGB>> indiviualPointClouds;

    //Merged Pointcloud
    pcl::PointCloud<pcl::PointXYZRGB> fullPointCloud;

    //TimeStamp
    double timeStamp = 0;
    
public:

    //List of foundobjects
    std::vector<FoundObject> objects;

    //Constructor
    Information3D();

    //Deconstructor
    ~Information3D();

    //Adds a vector of pointclouds to individual pointclouds
    void AddPointClouds(std::vector<pcl::PointCloud<pcl::PointXYZRGB>> pointClouds);

    void AddFullPointCloud(pcl::PointCloud<pcl::PointXYZRGB> pointCloud);
    
    void FindObjects();
    
    //Retrieves the merged pointcloud
    pcl::PointCloud<pcl::PointXYZRGB> getPointCloud();
    
    //Inserts an object into the object list
    void InsertObject(pcl::PointCloud<pcl::PointXYZRGB> segment);
    
    //Retrieves the list of found objects
    std::vector<FoundObject> getObjects();
    
    std::vector<pcl::PointCloud<pcl::PointXYZRGB>> getPointClouds();
    
    void setTimeStamp(double tStamp);
    
    double getTimeStamp();
};



