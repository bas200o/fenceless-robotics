#include "../include/CameraConnector.hpp"

CameraConnector::CameraConnector(/* args */)
{
}

CameraConnector::~CameraConnector()
{
}

CameraConnector *CameraConnector::pSingleton = NULL;

/**
 * Gets the instance for the singleton object.
 * @return Get the singleton object
 */
CameraConnector *CameraConnector::getInstance()
{
    if (pSingleton == NULL)
    {
        pSingleton = new CameraConnector();
    }
    return pSingleton;
}

void threadFunc(RSCameraHandler *handler)
{
    handler->runThread();
}

/**
 * Method connects the camera's to the application.
 * @param number The camera in the array
 * @param type Type of camera that gets connected: 1 for realsense, 2 for zed(//TODO)
 * @return void
 */
void CameraConnector::connectCameras(int number, int type)
{
    switch (type)
    {
    case 1:
    {
        RSCameraHandler* newCamera = new RSCameraHandler();
        if (newCamera->getPipeRunning()) {
            std::thread camThread(threadFunc, newCamera);
            camThread.detach();
            connectedCams.insert(connectedCams.begin() + number, newCamera);
        } else {
            std::cout << "RS camera handler failed to init" << std::endl;
        }
        break;
    }
    case 2:
        //zed
        break;

    case 3:
        //other
        break;

    default:
        break;
    }
}

std::vector<std::string> CameraConnector::getConnectedRSCameras()
{
    return CameraConnector::rsCameraIds;
}

void CameraConnector::addConnectedRSCamera(std::string id)
{
    CameraConnector::rsCameraIds.push_back(id);
}

void CameraConnector::remConnectedRSCamera(std::string id)
{
    for (size_t i = 0; i < CameraConnector::rsCameraIds.size(); i++)
    {
        if (id == CameraConnector::rsCameraIds.at(i))
        {
            CameraConnector::rsCameraIds.erase(CameraConnector::rsCameraIds.begin() + i);
        }
    }
}

/**
 * Method retrieves rgb image from connected camerera's
 * @return std vector with opencv rgb image not depth
 */
std::vector<cv::Mat> CameraConnector::retrieveImages()
{
    int s = sizeof(connectedCams);
    std::vector<cv::Mat> images;
    for (int i = 0; i < s; i++)
    {
        //image->add image form camera push back
    }
    return images;
}

/**
 * Method returns a vector of pointclouds from connected camera's
 * @return std vector with rgb pointclouds
 */
std::vector<pcl::PointCloud<pcl::PointXYZRGB>> CameraConnector::retrievePointClouds()
{
    float s = connectedCams.size();
    std::vector<pcl::PointCloud<pcl::PointXYZRGB>> pointclouds;
    std::tuple<pcl::PointCloud<pcl::PointXYZRGB>, double> cloudStamp;
    for(int i = 0; i<s ; i++) {
        cloudStamp = connectedCams.at(i)->getLatestPointCloudRGB();
        pointclouds.push_back(std::get<0>(cloudStamp));
    }
    CameraConnector::lastTimeStamp = std::get<1>(cloudStamp);
    return pointclouds;
}

double CameraConnector::getLastTimeStamp(){
    return lastTimeStamp;
}
