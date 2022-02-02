//Inheritence class for camera handlers, which connects the cameras to the system
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

    //number of the camera
    int cameraNumber;

    //name of the camera
    string name;

    //potentially port for the camera
    int port;

    //mutex to lock and unlock data on threads
    std::mutex latestCloud_mtx;
    std::mutex latestRGBCloud_mtx;

    //Newest recieved pointcloud, RGB pointcloud and image
    pcl::PointCloud<pcl::PointXYZ> latestCloud;
    pcl::PointCloud<pcl::PointXYZRGB> latestRGBCloud;

    cv::Mat latestImage;

    void setLatestCloud(pcl::PointCloud<pcl::PointXYZRGB> pointCloudRGB);

    void setLatestCloud(pcl::PointCloud<pcl::PointXYZ> pointCloud);

    void setLatestCloud(pcl::PointCloud<pcl::PointXYZRGB> pointCloudRGB, pcl::PointCloud<pcl::PointXYZ> pointCloud);

private:
    //converts different type of 3D image to pcl pointcloud
    virtual pcl::PointCloud<pcl::PointXYZ> convertToPCL() = 0;

    //converts different type of 2D image to cv Mat
    virtual cv::Mat convertToMatrix() = 0;

    //grabs the latest data from the camera
    virtual void grabImage() = 0;

    //connects the camera
    virtual void connectCamera() = 0;

public:
    double timeStamp;

    //retrieves the latest cloud
    virtual pcl::PointCloud<pcl::PointXYZ> getLatestPointCloud() = 0;

    virtual std::tuple<pcl::PointCloud<pcl::PointXYZRGB>, double> getLatestPointCloudRGB() = 0;

    //main loop of the handler thread
    virtual void runThread() = 0;
};