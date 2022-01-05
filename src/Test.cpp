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
#include <thread> // std::this_thread::sleep_for
#include <chrono>

int Omain()
{
  // Read in the cloud data
  pcl::PCDReader reader;
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>), cloud_f(new pcl::PointCloud<pcl::PointXYZRGB>);
  reader.read("/home/bas/Desktop/toolslog/Captured_Frame1.pcd", *cloud);
  std::cout << "PointCloud before filtering has: " << cloud->size() << " data points." << std::endl; //*

  // Create the filtering object: downsample the dataset using a leaf size of 1cm
  pcl::VoxelGrid<pcl::PointXYZRGB> vg;
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZRGB>);
  vg.setInputCloud(cloud);
  vg.setLeafSize(0.01f, 0.01f, 0.01f);
  vg.filter(*cloud_filtered);
  std::cout << "PointCloud after filtering has: " << cloud_filtered->size() << " data points." << std::endl; //*

  // Create the segmentation object for the planar model and set all the parameters
  pcl::SACSegmentation<pcl::PointXYZRGB> seg;
  pcl::PointIndices::Ptr inliers(new pcl::PointIndices);
  pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_plane(new pcl::PointCloud<pcl::PointXYZRGB>());
  pcl::PCDWriter writer;
  seg.setOptimizeCoefficients(true);
  seg.setModelType(pcl::SACMODEL_PLANE);
  seg.setMethodType(pcl::SAC_RANSAC);
  seg.setMaxIterations(100);
  seg.setDistanceThreshold(0.02);

  int nr_points = (int)cloud_filtered->size();
  while (cloud_filtered->size() > 0.3 * nr_points)
  {
    // Segment the largest planar component from the remaining cloud
    seg.setInputCloud(cloud_filtered);
    seg.segment(*inliers, *coefficients);
    if (inliers->indices.size() == 0)
    {
      std::cout << "Could not estimate a planar model for the given dataset." << std::endl;
      break;
    }

    // Extract the planar inliers from the input cloud
    pcl::ExtractIndices<pcl::PointXYZRGB> extract;
    extract.setInputCloud(cloud_filtered);
    extract.setIndices(inliers);
    extract.setNegative(false);

    // Get the points associated with the planar surface
    extract.filter(*cloud_plane);
    std::cout << "PointCloud representing the planar component: " << cloud_plane->size() << " data points." << std::endl;

    // Remove the planar inliers, extract the rest
    extract.setNegative(true);
    extract.filter(*cloud_f);
    *cloud_filtered = *cloud_f;
  }

  // Creating the KdTree object for the search method of the extraction
  pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZRGB>);
  tree->setInputCloud(cloud_filtered);

  std::vector<pcl::PointIndices> cluster_indices;
  pcl::EuclideanClusterExtraction<pcl::PointXYZRGB> ec;
  ec.setClusterTolerance(0.02); // 2cm
  ec.setMinClusterSize(100);
  ec.setMaxClusterSize(25000);
  ec.setSearchMethod(tree);
  ec.setInputCloud(cloud_filtered);
  ec.extract(cluster_indices);

  int j = 0;
  for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin(); it != cluster_indices.end(); ++it)
  {
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_cluster(new pcl::PointCloud<pcl::PointXYZRGB>);
    for (const auto &idx : it->indices)
      cloud_cluster->push_back((*cloud_filtered)[idx]); //*
    cloud_cluster->width = cloud_cluster->size();
    cloud_cluster->height = 1;
    cloud_cluster->is_dense = true;

    std::cout << "PointCloud representing the Cluster: " << cloud_cluster->size() << " data points." << std::endl;
    std::stringstream ss;
    ss << "cloud_cluster_" << j << ".pcd";
    writer.write<pcl::PointXYZRGB>(ss.str(), *cloud_cluster, false); //*
    j++;
  }

  // boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("Captured Frame")); //pcl visualisers

  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudView(new pcl::PointCloud<pcl::PointXYZRGB>);

  std::string openFileName = "cloud_cluster_9.pcd";//1 is frame
  pcl::io::loadPCDFile(openFileName, *cloudView); // Load .pcd File

  //==========================
  // Pointcloud Visualization
  //==========================
  // Create viewer object titled "Captured Frame"
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("Captured Frame"));

  // Set background of viewer to black
  viewer->setBackgroundColor(0, 0, 0);
  // Add generated point cloud and identify with string "Cloud"
  viewer->addPointCloud<pcl::PointXYZRGB>(cloudView, "Cloud");
  // Default size for rendered points
  viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "Cloud");
  // Viewer Properties
  viewer->initCameraParameters(); // Camera Parameters for ease of viewing

  cout << endl;
  cout << "Press [Q] in viewer to continue. " << endl;

  viewer->spinOnce();
        int p = 0;


  for (int i = 0; i < 2; i++)
  {
    if(i==0){
      p = 1;
    }
    else{
      p = 9;
    }
    viewer->removeAllPointClouds();
    openFileName = "cloud_cluster_" + std::to_string(p) + ".pcd";
    pcl::io::loadPCDFile(openFileName, *cloudView); // Load .pcd File
    viewer->setBackgroundColor(0, 0, 0);
    // Add generated point cloud and identify with string "Cloud"
    viewer->addPointCloud<pcl::PointXYZRGB>(cloudView, "Cloud");
    // Default size for rendered points
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "Cloud");
    // Viewer Properties
    viewer->initCameraParameters(); // Camera Parameters for ease of viewing

    cout << endl;
    cout << "Press [Q] in viewer to continue. " << endl;

    viewer->spinOnce(10000);
    
    //==========================
    // Pointcloud Visualization
    //==========================
    // Create viewer object titled "Captured Frame"
  }
  return (0);
}