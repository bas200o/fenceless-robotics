#include "../include/CameraHandler.hpp"

void CameraHandler::setLatestCloud(pcl::PointCloud<pcl::PointXYZRGB> pointCloudRGB){
    latestRGBCloud = pointCloudRGB;
}

void CameraHandler::setLatestCloud(pcl::PointCloud<pcl::PointXYZ> pointCloud){
    latestCloud = pointCloud;
}

void CameraHandler::setLatestCloud(pcl::PointCloud<pcl::PointXYZRGB> pointCloudRGB,  pcl::PointCloud<pcl::PointXYZ> pointCloud){
    latestRGBCloud = pointCloudRGB;
    latestCloud = pointCloud;   
}
    