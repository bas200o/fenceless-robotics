#include "../include/CameraHandler.hpp"

void CameraHandler::setLatestCloud(pcl::PointCloud<pcl::PointXYZRGB> pointCloudRGB)
{
    CameraHandler::latestRGBCloud_mtx.lock();
    CameraHandler::latestRGBCloud = pointCloudRGB;
    CameraHandler::latestRGBCloud_mtx.unlock();
}

void CameraHandler::setLatestCloud(pcl::PointCloud<pcl::PointXYZ> pointCloud)
{
    CameraHandler::latestCloud_mtx.lock();
    CameraHandler::latestCloud = pointCloud;
    CameraHandler::latestCloud_mtx.unlock();
}

void CameraHandler::setLatestCloud(pcl::PointCloud<pcl::PointXYZRGB> pointCloudRGB, pcl::PointCloud<pcl::PointXYZ> pointCloud)
{
    setLatestCloud(pointCloud);
    setLatestCloud(pointCloudRGB);
}
