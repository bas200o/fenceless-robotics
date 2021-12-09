#pragma once
#include "../include/CameraHandler.hpp"

class CameraConnector {
public:
   static CameraConnector* getInstance();
   void connectCameras(int number, int type);
private:
   CameraConnector();
   ~CameraConnector();
   static CameraConnector* pSingleton;		// CameraConnector instance
   CameraHandler* connectedCams[2];
};