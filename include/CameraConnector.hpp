/*Class used to connect camera handlers and keep track of them
/*This is a singleton so that only one object can keep track of the camerahandlers and the data will be retrievable from multiple classes
*/
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

class CameraConnector
{
public:
   //Vector of connected camera handlers
   std::vector<CameraHandler *> connectedCams;
   
   //retrieves the last timestamp
   double getLastTimeStamp();

   //Get the existing instance of camera connector
   static CameraConnector *getInstance();

   //Connects a camera of a type at position number
   void connectCameras(int number, int type);

   //Retrieves the last images from all camera handlers
   std::vector<cv::Mat> retrieveImages();

   //Retrieves the last pointclouds from all camera handlers
   std::vector<pcl::PointCloud<pcl::PointXYZRGB>> retrievePointClouds();

   //Lists as a quick fix so RSCamerHandler is working
   std::vector<std::string> getConnectedRSCameras();

   void addConnectedRSCamera(std::string id);

   void remConnectedRSCamera(std::string id);

private:

   //Is the last retrieved timestamp
   double lastTimeStamp;

   //CameraConnector instance
   static CameraConnector *pSingleton;

   //Lists as a quick fix so RSCamerHandler is working
   std::vector<std::string> rsCameraIds;

   //Connector
   CameraConnector();

   //Destructor
   ~CameraConnector();
};