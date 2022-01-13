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

RSCameraHandler camHandler;

void camTask() {
  camHandler.runThread();
}
// The function we want to execute on the new thread.
void task1(string msg)
{
    std::cout << "task1 says: " << msg;
}

int main()
{
  std::thread thing(camTask);
  
  
  std::this_thread::sleep_for(std::chrono::nanoseconds(1000));

  pcl::visualization::PCLVisualizer::Ptr viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  // pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
  // cloud* = camHandler.GetLatestPointCloud();

  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
  *cloud = camHandler.getLatestPointCloud();

  viewer->setBackgroundColor (0, 0, 0);
  viewer->addPointCloud(cloud);
  // viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1);
  viewer->initCameraParameters ();
  viewer->spinOnce();

    pcl::PointCloud<pcl::PointXYZ>::Ptr latestCloud(new pcl::PointCloud<pcl::PointXYZ>);
    *latestCloud = camHandler.getLatestPointCloud();
  while(true) {
    pcl::PointCloud<pcl::PointXYZ>::Ptr updateCloud(new pcl::PointCloud<pcl::PointXYZ>);
    *updateCloud = camHandler.getLatestPointCloud();

     *latestCloud = *updateCloud;
    
    viewer->removeAllPointClouds();
    viewer->addPointCloud(updateCloud);

    // viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1);

    viewer->spinOnce(200); 
  }
  
  thing.join();

}