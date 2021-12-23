#include "pclHelper.hpp"

using namespace pclHelperFunctions;

void pclHelper::showPCL(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud) {
  pcl::visualization::PCLVisualizer viewer;
  viewer.addPointCloud(cloud);
  viewer.spin();
}

pcl::PointCloud<pcl::PointXYZ>::Ptr pclHelper::loadPCL(std::string file_path) {
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  if (pcl::io::loadPCDFile(file_path, *cloud) == -1) //* load the file
  {
    PCL_ERROR ("Couldn't read file .pcd \n");
  }
  return cloud;
}

void pclHelper::savePCL(std::string file_path, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud) {
  if (pcl::io::savePCDFileASCII(file_path, *cloud) == -1) 
  {
    PCL_ERROR ("Couldn't save file .pcd \n");
  }
}

pcl::PointCloud<pcl::PointXYZ>::Ptr pclHelper::generatePCL() {
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  cloud->width=10;
  cloud->height=1;
  cloud->is_dense = false;
  cloud->points.resize(cloud->width * cloud->height);

  for (size_t i = 0; i < cloud->points.size(); ++i)
  {
    cloud->points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
    cloud->points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
    cloud->points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
  }
  return cloud;
}

pcl::PointCloud<pcl::PointXYZ>::Ptr pclHelper::combinePointClouds(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud1, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2) {
    pcl::PointCloud<pcl::PointXYZ>::Ptr recieving_cloud (new pcl::PointCloud<pcl::PointXYZ>);

    recieving_cloud->width=cloud1->size()+cloud2->size();
    recieving_cloud->height=1;
    recieving_cloud->is_dense = true;
    recieving_cloud->points.resize(recieving_cloud->width * recieving_cloud->height);

    size_t cloud1Size = cloud1->size();
    size_t cloud2Size = cloud2->size();

    for (size_t  i = 0; i < cloud1Size; i++) {
      recieving_cloud->points[i].x = cloud1->points[i].x;
      recieving_cloud->points[i].y = cloud1->points[i].y;
      recieving_cloud->points[i].z = cloud1->points[i].z;
    }

    for (size_t  i = 0; i < cloud2Size; i++) {
      recieving_cloud->points[i + cloud1Size].x = cloud2->points[i].x;
      recieving_cloud->points[i + cloud1Size].y = cloud2->points[i].y;
      recieving_cloud->points[i + cloud1Size].z = cloud2->points[i].z;
    }

    return recieving_cloud;
}