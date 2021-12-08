#include "../include/RSCameraHandler.hpp"

RSCameraHandler::RSCameraHandler(/* args */)
{
}

RSCameraHandler::~RSCameraHandler()
{
}

pcl::PointCloud<pcl::PointXYZRGB> RSCameraHandler::convertToPCL(){
    return latestPointCloud;
}

void RSCameraHandler::setLatestCloud(pcl::PointCloud<pcl::PointXYZRGB> pointCloud){

}

void RSCameraHandler::grabImage(){

}

void RSCameraHandler::runThreat(){

}

void RSCameraHandler::connectCamera(){
    
}