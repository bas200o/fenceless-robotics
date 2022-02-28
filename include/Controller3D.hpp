/*Class used for all 3D vision and makes objects with information
/*gets the images from the CameraConnector
*/

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
#include <pcl/common/angles.h>
#include "../include/SettingSingleton.hpp"
#include "../include/GUIData.hpp"

class Controller3D
{
    private:
        //Array with the last 5 info of progressed pointclouds
        Information3D lastInfo[5];
        pcl::visualization::PCLVisualizer::Ptr viewer;
        int identificationNumber = 0;

    public:
        //Constructor
        Controller3D();
        
        //Destructor
        ~Controller3D();
        
        //Does object detection/segmentation on the information passed
        void DetectObjects(int pCloud);
        
        // Draw the new objects in the PCLVisualizer
        void RepaintVisualizer();
        
        //Procceses the new point cloud  only works with 2 cams
        void ProccesPointcloud();
        
        //Creates information from by receiving the pointclouds from CameraConnector
        void CreateNewInformation();
        
        //Combines the pointclouds from pointcloudinfo lastinfo[pcloud]
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr CombinePointClouds(int pCloud);
        
        //Calculates the speed of object by comparing them to either the previous pointcloud or the one before
        void CalculateSpeed();
        
        //
        void calculateDirection();
        //
        void pushUIData();
        
        //
        void configure();
        //
        void assignIdentification();
        //Rotates a pointcloud based on the settings in SettingSingleton
        static pcl::PointCloud<pcl::PointXYZRGB>::Ptr rotatePCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGCloud);
        
        //Rotates a pointcloud based on the settings provided
        static pcl::PointCloud<pcl::PointXYZRGB>::Ptr rotatePCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGCloud, rotationSettings rs);
        
        //Rotates a pointcloud based on passed variables
        static pcl::PointCloud<pcl::PointXYZRGB>::Ptr rotatePCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGCloud,
                                                                float x, float y, float z);
        
        //Moves a pointcloud based on the settings in SettingSingleton
        static pcl::PointCloud<pcl::PointXYZRGB>::Ptr movePCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGcloud);
        
        //Moves a pointcloud based on the settings in SettingSingleton
        static pcl::PointCloud<pcl::PointXYZRGB>::Ptr movePCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGcloud, moveSettings ms);
        
        //Moves a pointcloud based on passed variables
        static pcl::PointCloud<pcl::PointXYZRGB>::Ptr movePCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGcloud,
                                                                float x, float y, float z);
        
        //Filters a pointcloud based on the settings in SettingSingleton
        static pcl::PointCloud<pcl::PointXYZRGB>::Ptr filterPCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGCloud);
        static pcl::PointCloud<pcl::PointXYZRGB>::Ptr filterPCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGCloud, filterSettings fs);
        //Filters a pointcloud based on passed variables
        static pcl::PointCloud<pcl::PointXYZRGB>::Ptr filterPCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGCloud,
                                                                float x, float x1, float y, float y1, float z, float z1);

};
