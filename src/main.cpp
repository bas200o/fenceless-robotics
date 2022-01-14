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

#include "../include/RSCameraHandler.hpp"
#include "../include/SettingSingleton.hpp"
#include "../include/Controller3D.hpp"

#include "../include/DataManager.hpp"

#include <vector>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QTableView>
#include <QTableWidget>

RSCameraHandler camHandler;

void camTask()
{
  camHandler.runThread();
}
// The function we want to execute on the new thread.
void task1(string msg)
{
  std::cout << "task1 says: " << msg;
}

int testmain()
{
  SettingSingleton *ds = ds->getInstance();
  struct rotationSettings rs = {0.0, 0.0, 1.0};
  ds->setRotate(rs);
  struct moveSettings ms = {0.0, 0.0, 0.0};
  ds->setMove(ms);
  struct filterSettings fs = {-1.0, -1.0, -1.0, 1.0, 1.0, 1.0};
  ds->setFilter(fs);

  std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
  std::thread thing(camTask);
  
  pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));

  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
  *cloud = camHandler.getLatestPointCloud();

  viewer->setBackgroundColor(0, 0, 0);
  viewer->addPointCloud(cloud);
  // viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1);
  viewer->initCameraParameters();
  viewer->spinOnce();

  pcl::PointCloud<pcl::PointXYZRGB>::Ptr prevCloud(new pcl::PointCloud<pcl::PointXYZRGB>);
  *prevCloud = std::get<0>(camHandler.getLatestPointCloudRGB());
  while (true)
  {
    // pcl::PointCloud<pcl::PointXYZRGB>::Ptr rgbcloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr currentCloud(new pcl::PointCloud<pcl::PointXYZRGB>);

    *currentCloud = std::get<0>(camHandler.getLatestPointCloudRGB());

    currentCloud = Controller3D::rotatePCL(currentCloud);

    // currentCloud = Controller3D::movePCL(currentCloud);

    // currentCloud = Controller3D::filterPCL(currentCloud);

    viewer->removeAllPointClouds();
    viewer->addPointCloud(currentCloud);

    // viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1);

    viewer->spinOnce(200);

    *prevCloud = *currentCloud;
  }

  thing.join();
}

int task2(int argc, char *argv[])
{
  return testmain();
}

int main(int argc, char *argv[])
{
  std::thread t1(task2, argc, argv);

  return maingui(argc, argv);
}