/*Class used to connect camera handlers and keep track of them*/
#pragma once
#include "../include/CameraHandler.hpp"
#include "../include/RSCameraHandler.hpp"
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <cstdlib>
#include <thread>

class CameraConnector {
public:
   static CameraConnector* getInstance();
   void connectCameras(int number, int type);
   std::vector<CameraHandler*> connectedCams;
   std::vector<cv::Mat> retrieveImages();
   std::vector<pcl::PointCloud<pcl::PointXYZRGB>> retrievePointClouds();
   std::vector<std::string> getConnectedRSCameras();
   void addConnectedRSCamera(std::string id);
   void remConnectedRSCamera(std::string id);
private:
   CameraConnector();
   ~CameraConnector();
   static CameraConnector* pSingleton;		// CameraConnector instance
   std::vector<std::string> rsCameraIds;

};