#include <iostream>
#include <algorithm>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <string>

// Intel Realsense Headers
#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/common/common_headers.h>
#include <pcl/features/normal_3d.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>
#include <boost/thread/thread.hpp>
#include <pcl/io/io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/search/kdtree.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <thread>
#include <chrono>

#include "../include/SettingSingleton.hpp"
#include "../include/Controller3D.hpp"

#include "../include/DataManager.hpp"

#include <vector>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QTableView>
#include <QTableWidget>

// RSCameraHandler camHandler;

// void camTask()
// {
//   camHandler.runThread();
// }
// // The function we want to execute on the new thread.
// void task1(string msg)
// {
//   std::cout << "task1 says: " << msg;
// }

int testmain()
{
  SettingSingleton *ds = ds->getInstance();
  struct rotationSettings rs = {0.0, 0.0, 1.0};
  ds->setRotate(rs);
  struct moveSettings ms = {0.0, 0.0, 0.0};
  ds->setMove(ms);
  struct filterSettings fs = {-1.0, -1.0, -1.0, 1.0, 1.0, 1.0};
  ds->setFilter(fs);

  std::this_thread::sleep_for(std::chrono::nanoseconds(10000));
  CameraConnector *camCon = CameraConnector::getInstance();
  pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));

  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud2(new pcl::PointCloud<pcl::PointXYZRGB>);

    auto pointclouds = camCon->retrievePointClouds();

    *cloud  = pointclouds.at(0);
    *cloud2 = pointclouds.at(1);
  
  for (size_t i = 0; i < cloud2->points.size(); i++)
    {
      cloud->points[i].g = 0;
      cloud->points[i].b = 0;
    }


  viewer->setBackgroundColor(0, 0, 0);
  viewer->addPointCloud(cloud, "cloud1");
  viewer->addPointCloud(cloud2, "cloud2");
  // viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1);
  viewer->initCameraParameters();
  viewer->spinOnce();



  while (true)
  {
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudCopy(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::copyPointCloud(*cloud, *cloudCopy);
    cloudCopy = Controller3D::rotatePCL(cloudCopy);
    cloudCopy = Controller3D::movePCL(cloudCopy);
    
    // currentCloud = Controller3D::filterPCL(currentCloud);

    // viewer->removeAllPointClouds();
    viewer->updatePointCloud(cloudCopy,  "cloud1");
    viewer->updatePointCloud(cloud2, "cloud2"); 

    // viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1);

    viewer->spinOnce(200);
  }
}


int task2(int argc, char *argv[])
{
  return testmain();
}

int main(int argc, char *argv[])
{
  CameraConnector *camCon = CameraConnector::getInstance();
  camCon->connectCameras(0, 1);
  camCon->connectCameras(1, 1);
  // het();
  std::thread t1(task2, argc, argv);

  return maingui(argc, argv);
}