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
};


