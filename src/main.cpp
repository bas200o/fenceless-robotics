#include <iostream>
#include <thread>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/common/angles.h> // for pcl::deg2rad
#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>

using namespace std::chrono_literals;

pcl::visualization::PCLVisualizer::Ptr simpleVis (pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud)
{
  // --------------------------------------------
  // -----Open 3D viewer and add point cloud-----
  // --------------------------------------------
  pcl::visualization::PCLVisualizer::Ptr viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->setBackgroundColor (0, 0, 0);
  viewer->addPointCloud<pcl::PointXYZ> (cloud, "sample cloud");
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");
  viewer->addCoordinateSystem (1.0);
  viewer->initCameraParameters ();
  return (viewer);
}

int main (int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  
  // Fill in the cloud data
  cloud->width=5;
  cloud->height=1;
  cloud->is_dense = false;
  cloud->points.resize(cloud->width * cloud->height);

  for (size_t i = 0; i < cloud->points.size(); ++i)
  {
    cloud->points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
    cloud->points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
    cloud->points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
  }

   pcl::visualization::CloudViewer viewer ("Simple Cloud Viewer");
   viewer.showCloud(cloud, "cloud");
   while (!viewer.wasStopped())
   {
   }
    return 0;

//   pcl::visualization::PCLVisualizer::Ptr viewer;
//   viewer = simpleVis(cloud);

//   while (!viewer->wasStopped())
//   {
//     viewer->spinOnce (100);
//     std::this_thread::sleep_for(100ms);
//   }

  return (0);
}

// // License: Apache 2.0. See LICENSE file in root directory.
// // Copyright(c) 2015-2017 Intel Corporation. All Rights Reserved.

// #include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
// // #include "example.hpp"          // Include short list of convenience functions for rendering

// #include <algorithm>            // std::min, std::max
// #include <iostream>

// #include <pcl/io/pcd_io.h>
// #include <pcl/point_types.h>
// #include <pcl/visualization/cloud_viewer.h>
// #include <pcl/visualization/pcl_visualizer.h>

// int main()
// {


//     // Declare pointcloud object, for calculating pointclouds and texture mappings
//     rs2::pointcloud pc;
//     // We want the points object to be persistent so we can display the last cloud when a frame drops
//     rs2::points points;

//     // Declare RealSense pipeline, encapsulating the actual device and sensors
//     rs2::context ctx;
//     rs2::pipeline pipe;
//     // Start streaming with default recommended configuration
//     pipe.start();


//         // Wait for the next set of frames from the camera
//         auto frames = pipe.wait_for_frames();

//         auto color = frames.get_color_frame();

//         // For cameras that don't have RGB sensor, we'll map the pointcloud to infrared instead of color
//         if (!color)
//             color = frames.get_infrared_frame();

//         // Tell pointcloud object to map to this color frame
//         pc.map_to(color);

//         auto depth = frames.get_depth_frame();

//         // Generate the pointcloud and texture mappings
//         points = pc.calculate(depth);

//         auto vertices = points.get_vertices();

//         std::cout << "hello from librealsense - " << RS2_API_VERSION_STR << std::endl;
//         std::cout << "You have " << ctx.query_devices().size() << " RealSense devices connected" << std::endl;

//         // for (size_t i = 0; i < points.size(); i++) {
//         //     std::cerr << "      " << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << std::endl;
//         // }

//         pcl::PointCloud<pcl::PointXYZ> cloud;

//         std::cout << points.size() << std::endl;

//         float usable_points[points.size()][3];
//         int usable_point_count = 0;

//         for (size_t i = 0; i < points.size(); i++) {
//         if (vertices[i].x != 0 || vertices[i].y != 0 || vertices[i].z != 0) {
//             usable_points[usable_point_count][0] = vertices[i].x;
//             usable_points[usable_point_count][1] = vertices[i].y;
//             usable_points[usable_point_count][2] = vertices[i].z;
//             usable_point_count++;
//         }
//     }

// //Filters 
//     usable_point_count++;
//     cloud.width = usable_point_count;;
//     cloud.height = 1;
//     cloud.is_dense = false;
//     cloud.points.resize(usable_point_count);

//     for (size_t i = 0; i < usable_point_count; i++) {
//         cloud.points[i].x = usable_points[i][0];
//         cloud.points[i].y = usable_points[i][1];
//         cloud.points[i].z = usable_points[i][2];
//     }


//     pcl::io::savePCDFileASCII("test_pcd.pcd", cloud);
//     std::cerr << "Saved " << cloud.points.size() << " data points to test_pcd.pcd." << std::endl;
   

//     return 0;
// }




// #include <librealsense2/rs.hpp>
// #include <librealsense2/hpp/rs_internal.hpp>
// #include <iostream>

// #include <pcl/io/pcd_io.h>
// #include <pcl/point_types.h>
// #include <pcl/visualization/cloud_viewer.h>
// #include <pcl/visualization/pcl_visualizer.h>

// int main()
// {
//     rs2::context ctx;

//     std::cout << "hello from librealsense - " << RS2_API_VERSION_STR// #include <pcl/io/pcd_io.h>
// #include <pcl/point_types.h>
// #include <pcl/visualization/cloud_viewer.h>
// #include <pcl/visualization/pcl_visualizer.h> << std::endl;
//     std::cout << "You have " << ctx.query_devices().size() << " RealSense devices connected" << std::endl;


// rs2::pipeline pipe;
// rs2::pipeline_profile selection = pipe.start();
// auto depth_stream = selection.get_stream(RS2_STREAM_DEPTH);
// auto color_stream = selection.get_stream(RS2_STREAM_COLOR);
// rs2_extrinsics e = depth_stream.get_extrinsics_to(color_stream);
// // Apply extrinsics to the origin
// float origin[3] { 0.f, 0.f, 0.f };
// float target[3];
// rs2_transform_point_to_point(target, &e, origin);


//     pcl::PointCloud<pcl::PointXYZRGB> cloud;

//     //fill coud with data,

    


//     cloud.width = 100;
//     cloud.height = 1;
//     cloud.is_dense = false;
//     cloud.points.resize(cloud.width * cloud.height);

//     for (size_t i = 0; i < cloud.points.size(); i++) {
//         cloud.points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
//         cloud.points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
//         cloud.points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
//         cloud.points[i].r = 255 * rand() / (RAND_MAX + 1.0f);
//         cloud.points[i].g = 255 * rand() / (RAND_MAX + 1.0f);
//         cloud.points[i].b = 255 * rand() / (RAND_MAX + 1.0f);
//     }


//     pcl::io::savePCDFileASCII("test_pcd.pcd", cloud);
//     std::cerr << "Saved " << cloud.points.size() << " data points to test_pcd.pcd." << std::endl;

//     // for (size_t i = 0; i < cloud.points.size(); i++) {
//     //     std::cerr << "      " << cloud.points[i].x << " " << cloud.points[i].y << " " << cloud.points[i].z << std::endl;
//     // }

//     // pcl::PointCloud<pcl::PointXYZRGB>::Ptr hey (&cloud);

    
    
//   // pcl::io::loadPCDFile("./test_pcd.pcd", *hey);
//   //... populate cloud

//   //  pcl::visualization::CloudViewer viewer ("Simple Cloud Viewer");
//   // //  viewer.showCloud(hey, "cloud");
//   //  while (!viewer.wasStopped())
//   //  {
//   //  }
//   //   return 0;

//   // pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("PCLVisualizer", false));
//   // int viewPlane = -1;
//   // viewer->createViewPort(0.0, 0.0, 1.0, 1.0, viewPlane);
//   // viewer->addCoordinateSystem(5.0);
//   // viewer->setBackgroundColor(0.2, 0.2, 0.2/*, viewPlane*/);
//   return 0;
// }




// // #include <pcl/visualization/cloud_viewer.h>
// // #include <iostream>
// // #include <pcl/io/io.h>
// // #include <pcl/io/pcd_io.h>
    
// // int user_data;
    
// // void 
// // viewerOneOff (pcl::visualization::PCLVisualizer& viewer)
// // {
// //     viewer.setBackgroundColor (1.0, 0.5, 1.0);
// //     pcl::PointXYZ o;
// //     o.x = 1.0;
// //     o.y = 0;
// //     o.z = 0;
// //     viewer.addSphere (o, 0.25, "sphere", 0);
// //     std::cout << "i only run once" << std::endl;
    
// // }
    
// // void 
// // viewerPsycho (pcl::visualization::PCLVisualizer& viewer)
// // {
// //     static unsigned count = 0;
// //     std::stringstream ss;
// //     ss << "Once per viewer loop: " << count++;
// //     viewer.removeShape ("text", 0);
// //     viewer.addText (ss.str(), 200, 300, "text", 0);
    
// //     //FIXME: possible race condition here:
// //     user_data++;
// // }
    
// // int 
// // main ()
// // {
// //     pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>);

// //   if (pcl::io::loadPCDFile<pcl::PointXYZRGB> ("test_pcd.pcd", *cloud) == -1) //* load the file
// //   {
// //     PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
// //     return (-1);
// //   }

// //     // pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGBA>);
// //     // pcl::io::loadPCDFile ("test_pcd.pcd", *cloud);
    
// //     pcl::visualization::CloudViewer viewer("Cloud Viewer");
    
// //     //blocks until the cloud is actually rendered
// //     viewer.showCloud(cloud);
    
// //     //use the following functions to get access to the underlying more advanced/powerful
// //     //PCLVisualizer
    
// //     //This will only get called once
// //     viewer.runOnVisualizationThreadOnce (viewerOneOff);
    
// //     //This will get called once per visualization iteration
// //     viewer.runOnVisualizationThread (viewerPsycho);
// //     while (!viewer.wasStopped ())
// //     {
// //     //you can also do cool processing here
// //     //FIXME: Note that this is running in a separate thread from viewerPsycho
// //     //and you should guard against race conditions yourself...
// //     user_data++;
// //     }
// //     return 0;
// // }

// // #include <iostream>
// // #include <pcl/io/pcd_io.h>
// // #include <pcl/point_types.h>



// // int
// // main (int argc, char** argv)
// // {
// //   pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>);

// //   if (pcl::io::loadPCDFile<pcl::PointXYZRGB> ("test_pcd.pcd", *cloud) == -1) //* load the file
// //   {
// //     PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
// //     return (-1);
// //   }
// //   std::cout << "Loaded "
// //             << cloud->width * cloud->height
// //             << " data points from test_pcd.pcd with the following fields: "
// //             << std::endl;
// //   for (size_t i = 0; i < cloud->points.size (); ++i)
// //     std::cout << "    " << cloud->points[i].x
// //               << " "    << cloud->points[i].y
// //               << " "    << cloud->points[i].z << std::endl;




// //   return (0);
// // }   