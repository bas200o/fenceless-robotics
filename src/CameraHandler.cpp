#include "../include/CameraHandler.hpp"

void CameraHandler::setLatestCloud(pcl::PointCloud<pcl::PointXYZRGB> pointCloud){
    latestCloud = pointCloud;
}
