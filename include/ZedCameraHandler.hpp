/*Class that uses interface cameraHandler to create PCL and image data from Zed*/

#pragma once
#include "../include/CameraHandler.hpp"
class ZedCameraHandler : public CameraHandler
{
private:
    
public:
    ZedCameraHandler(/* args */);
    ~ZedCameraHandler();
};

