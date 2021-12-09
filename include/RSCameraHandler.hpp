#pragma once
#include "../include/CameraHandler.hpp"
#include <librealsense2/rs.hpp>
#include <librealsense2/hpp/rs_internal.hpp>
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

class RSCameraHandler : public CameraHandler
{
private:
    pcl::PointCloud<pcl::PointXYZRGB> convertToPCL(); 
    cv::Mat convertToMatrix();

    void setLatestCloud(pcl::PointCloud<pcl::PointXYZRGB> pointCloud);
    void grabImage();
    void runThreat();
    void connectCamera();
    rs2::context ctx;
    rs2::pipeline pipe;
    rs2::frameset frames;
    rs2::config config;

    
public:
    RSCameraHandler(/* args */);
    ~RSCameraHandler();
};


