
#pragma once
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

class CameraHandler
{
protected:
    int cameraNumber;
    string name;
    int port;

    std::mutex latestCloud_mtx;
    std::mutex latestRGBCloud_mtx;
    pcl::PointCloud<pcl::PointXYZ> latestCloud;
    pcl::PointCloud<pcl::PointXYZRGB> latestRGBCloud;
    cv::Mat latestImage;

    void setLatestCloud(pcl::PointCloud<pcl::PointXYZRGB> pointCloudRGB);
    void setLatestCloud(pcl::PointCloud<pcl::PointXYZ> pointCloud);
    void setLatestCloud(pcl::PointCloud<pcl::PointXYZRGB> pointCloudRGB, pcl::PointCloud<pcl::PointXYZ> pointCloud);

private:
    virtual pcl::PointCloud<pcl::PointXYZ> convertToPCL() = 0;
    virtual cv::Mat convertToMatrix() = 0;

    virtual void grabImage() = 0;
    virtual void connectCamera() = 0;

public:
    virtual pcl::PointCloud<pcl::PointXYZ> getLatestPointCloud() = 0;
    virtual pcl::PointCloud<pcl::PointXYZRGB> getLatestPointCloudRGB() = 0;

    virtual void runThread() = 0;
    
};