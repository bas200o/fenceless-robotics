/*Class that uses interface cameraHandler to create PCL and image data from Zed
/*Currently empty because no Zed camera has been used for this phase
*/
#pragma once
#include "../include/CameraHandler.hpp"
class ZedCameraHandler : public CameraHandler
{
public:
    //Constructor
    ZedCameraHandler();
    //Destructor
    ~ZedCameraHandler();
};
