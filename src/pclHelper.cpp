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
    PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
  }
  return cloud;
}

pcl::PointCloud<pcl::PointXYZ>::Ptr pclHelper::generatePCL() {
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  cloud->width=10;
  cloud->height=2;
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