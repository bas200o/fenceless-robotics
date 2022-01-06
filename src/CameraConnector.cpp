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

void CameraConnector::connectCameras(int number, int type){
    switch (type)
    {
    case 1:
    {
        printf("yeet \n");
        RSCameraHandler* newCamera = new RSCameraHandler();
        //newCamera->runThread();
        connectedCams.push_back(newCamera);
        connectedCams[0]->runThread();
        printf("yoot \n");
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
    for(int i = 0; i<s ; i++){
        printf("connectedcams \n");
        //pointcloud->add Pointcloud from camera push back
        pcl::PointCloud<pcl::PointXYZRGB> temp = connectedCams[i]->getLatestPointCloudRGB();
        pointclouds.push_back(temp);
    }
        return pointclouds;

}