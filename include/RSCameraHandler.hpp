/*Class that uses interface cameraHandler to create PCL and image data from realsense*/
#pragma once
#include "../include/CameraHandler.hpp"
#include <librealsense2/rs.hpp>
#include <librealsense2/hpp/rs_internal.hpp>
#include <iostream>
#include <thread>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <boost/thread.hpp>

using namespace cv;

class RSCameraHandler : public CameraHandler
{
private:
    std::tuple<pcl::PointCloud<pcl::PointXYZRGB>, pcl::PointCloud<pcl::PointXYZ>> convertBothPCL();
    pcl::PointCloud<pcl::PointXYZRGB> convertToRGBPCL(); 
    pcl::PointCloud<pcl::PointXYZ> convertToPCL();
    cv::Mat convertToMatrix();

    void grabImage();
    void connectCamera();
    void setLatestCloud(pcl::PointCloud<pcl::PointXYZ> pointCloud);
    rs2::context ctx;
    rs2::pipeline pipe;
    rs2::frameset frames;
    rs2::config config;

    rs2::points points;

    bool pipeRunning = false;



    
public:
    RSCameraHandler(/* args */);
    ~RSCameraHandler();
    pcl::PointCloud<pcl::PointXYZ> getLatestPointCloud();
    pcl::PointCloud<pcl::PointXYZRGB> getLatestColloredPointCloud();
    void runThreat();
    void threadRunner();
};


