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

class CameraHandler{
    protected: 
        int cameraNumber;
        string name; 
        int port;
        pcl::PointCloud<pcl::PointXYZRGB> latestCloud;
        cv::Mat latestImage;

    private:
        virtual pcl::PointCloud<pcl::PointXYZRGB> convertToPCL() = 0;
        virtual cv::Mat convertToMatrix() = 0;

        void setLatestCloud(pcl::PointCloud<pcl::PointXYZRGB> pointCloud);
        virtual void grabImage() = 0;
        virtual void runThreat() = 0;
        virtual void connectCamera() = 0;
};