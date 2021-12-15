/*Class that uses interface cameraHandler to create PCL and image data from realsense*/
#include "../include/CameraHandler.hpp"
#include <librealsense2/rs.hpp>
#include <librealsense2/hpp/rs_internal.hpp>
#include <iostream>

class RSCameraHandler : public CameraHandler
{
private:
    pcl::PointCloud<pcl::PointXYZRGB> convertToPCL();
    void setLatestCloud(pcl::PointCloud<pcl::PointXYZRGB> pointCloud);
    void grabImage();
    void runThreat();
    void connectCamera();
    pcl::PointCloud<pcl::PointXYZRGB> latestPointCloud;
    
public:
    RSCameraHandler(/* args */);
    ~RSCameraHandler();
};


