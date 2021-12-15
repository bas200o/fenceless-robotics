/*Class used to connect camera handlers and keep track of them*/
#pragma once
#include "../include/CameraHandler.hpp"
class CameraConnector
{
private:
    CameraConnector(/* args */);
    ~CameraConnector();
    CameraConnector(CameraConnector const&);
    void operator = (CameraConnector const&);
    CameraHandler* connectedCams[2];

public:
    static CameraConnector& GetInstance();
    
    void operator-(CameraConnector const&) = delete;
    void connectCameras(int number, int type);

    
};


