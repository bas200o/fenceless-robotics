/*Class used for all 3D vision and makes objects with information
get the images from the CameraConnector*/

#pragma once
#include "../include/Information3D.hpp"
#include "../include/FoundObject.hpp"
#include "../include/CameraConnector.hpp"
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/search/kdtree.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>

class Controller3D
{
private:
    /* data */
    //Calculatestuff
    Information3D lastInfo[5];

public:
    Controller3D(/* args */);
    ~Controller3D();
    void DetectObjects(int pCloud);
    void RemoveBackground(int pCloud);
    void CreateNewInformation();
    void CombinePointClouds(int pCloud);
    void CalculateSpeed(int pCloud);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr rotatePCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGCloud, float x, float y, float z);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr movePCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGcloud, float x, float y, float z);
    pcl::PointCloud<pcl::PointXYZ>::Ptr filterPCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGCloud, float x, float x1, float y, float y1, float z, float z1);
};
