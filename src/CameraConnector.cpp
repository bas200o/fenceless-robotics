#include "../include/CameraConnector.hpp"

CameraConnector::CameraConnector(/* args */)
{

}

CameraConnector::~CameraConnector()
{

}

CameraConnector* CameraConnector::pSingleton= NULL;

CameraConnector* CameraConnector::getInstance()
{
	if (pSingleton== NULL) {
		pSingleton = new CameraConnector();
	}
	return pSingleton;
}

void threadFunc(RSCameraHandler* handler) {
    handler->runThread();
}

void CameraConnector::connectCameras(int number, int type){
    switch (type)
    {
    case 1:
    {
        RSCameraHandler* newCamera = new RSCameraHandler();
        if (newCamera->getPipeRunning()) {
            std::thread thing(threadFunc, newCamera);
            thing.detach();
            connectedCams.insert(connectedCams.begin() + number, newCamera);
            // connectedCams.push_back(newCamera);
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

std::vector<std::string> CameraConnector::getConnectedRSCameras() {
    return CameraConnector::rsCameraIds;
}

void CameraConnector::addConnectedRSCamera(std::string id) {
    CameraConnector::rsCameraIds.push_back(id);
}

void CameraConnector::remConnectedRSCamera(std::string id) {
    for (size_t i = 0; i < CameraConnector::rsCameraIds.size(); i++)
    {
            if (id == CameraConnector::rsCameraIds.at(i)) {
                CameraConnector::rsCameraIds.erase(CameraConnector::rsCameraIds.begin() + i);
            }
    }
}

std::vector<cv::Mat> CameraConnector::retrieveImages(){
    int s = sizeof(connectedCams);
    std::vector<cv::Mat> images;
    for(int i = 0; i<s ; i++){
        //image->add image form camera push back
    }
    return images;
}

std::vector<pcl::PointCloud<pcl::PointXYZRGB>> CameraConnector::retrievePointClouds(){
    float s = connectedCams.size();
    std::vector<pcl::PointCloud<pcl::PointXYZRGB>> pointclouds;
    for(int i = 0; i<s ; i++) {
        pointclouds.push_back(connectedCams.at(i)->getLatestPointCloudRGB());
    }
    return pointclouds;
}