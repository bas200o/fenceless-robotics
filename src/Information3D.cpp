#include "../include/Information3D.hpp"

Information3D::Information3D(/* args */)
{
}

Information3D::~Information3D()
{
}

void Information3D::AddPointClouds(std::vector<pcl::PointCloud<pcl::PointXYZRGB>> pointClouds){
    indiviualPointClouds = pointClouds;
    return;
}

void Information3D::AddFullPointCloud(pcl::PointCloud<pcl::PointXYZRGB> pointCloud){
    fullPointCloud = pointCloud;
}

void Information3D::FindObjects(){
    
}

pcl::PointCloud<pcl::PointXYZRGB> Information3D::GetPointCloud(){
    return fullPointCloud;
}

void Information3D::InsertObject(pcl::PointCloud<pcl::PointXYZRGB> segment){
    FoundObject obj(segment);
    objects.push_back(obj);
    return;
}

std::vector<FoundObject> Information3D::getObjects(){
    return objects;
}

std::vector<pcl::PointCloud<pcl::PointXYZRGB>> Information3D::getPointClouds(){
    return indiviualPointClouds;
}
