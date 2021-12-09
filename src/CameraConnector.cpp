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
        //rs
        break;
    
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
//CameraConnector::CameraConnector(CameraConnector const&) = delete;

