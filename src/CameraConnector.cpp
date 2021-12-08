#include "../include/CameraConnector.hpp"

CameraConnector::CameraConnector(/* args */)
{
}

CameraConnector::~CameraConnector()
{
}

CameraConnector& CameraConnector::GetInstance(){
    static CameraConnector instance;
    return instance;
}

//CameraConnector::CameraConnector(CameraConnector const&) = delete;

