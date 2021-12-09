#include "../include/RSCameraHandler.hpp"


RSCameraHandler::RSCameraHandler(/* args */)
{
}

RSCameraHandler::~RSCameraHandler()
{
}

cv::Mat RSCameraHandler::convertToMatrix(){
    //return has to be changed, this is placeholder
    return latestImage;
}

pcl::PointCloud<pcl::PointXYZRGB> RSCameraHandler::convertToPCL(){
    //return has to be changed, this is placeholder
    return latestCloud;
}

void RSCameraHandler::setLatestCloud(pcl::PointCloud<pcl::PointXYZRGB> pointCloud){

}

void RSCameraHandler::grabImage(){
    frames = pipe.wait_for_frames();
    rs2::depth_frame depth = frames.get_depth_frame();
    rs2::frame color = frames.get_color_frame();

}

void RSCameraHandler::runThreat(){
    //config.enable_device()
    pipe.start(config);
    while(true){
        grabImage();
    }
}

void RSCameraHandler::connectCamera(){
    
}