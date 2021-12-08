#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>

using namespace std;
class CameraHandler{
    protected: 
        int cameraNumber;
        string name; 
        int port;
        pcl::PointCloud<pcl::PointXYZRGB> latestCloud;


    private:
        virtual pcl::PointCloud<pcl::PointXYZRGB> convertToPCL() = 0;
        void setLatestCloud(pcl::PointCloud<pcl::PointXYZRGB> pointCloud);
        virtual void grabImage() = 0;
        virtual void runThreat() = 0;
        virtual void connectCamera() = 0;
};