/***********************************************************
 * 
 *  Author Bas200o Lucas.exe
 * 
 *  TEST CODE ONLY NOT PRODUCTION READY
 * 
 ***********************************************************/

#include <iostream>
#include <algorithm>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <string>

// Intel Realsense Headers
#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API

// PCL Headers
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
// pcl transformation
#include <pcl/common/transforms.h>
// pcl filter
#include <pcl/filters/passthrough.h>

using namespace std;

// Prototypes
void Load_PCDFile(void);
bool userInput(void);
void cloudViewer(void);

// Global Variables
string cloudFile;
string prevFrameFile;
boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("Captured Frame"));
boost::shared_ptr<pcl::visualization::PCLVisualizer> transViewer(new pcl::visualization::PCLVisualizer("transformed Frame"));
boost::shared_ptr<pcl::visualization::PCLVisualizer> filterdViewer(new pcl::visualization::PCLVisualizer("filterd Frame"));

//======================================================
// RGB Texture
// - Function is utilized to extract the RGB data from
// a single point return R, G, and B values.
// Normals are stored as RGB components and
// correspond to the specific depth (XYZ) coordinate.
// By taking these normals and converting them to
// texture coordinates, the RGB components can be
// "mapped" to each individual point (XYZ).
//======================================================
std::tuple<int, int, int> RGB_Texture(rs2::video_frame texture, rs2::texture_coordinate Texture_XY)
{
  // Get Width and Height coordinates of texture
  int width = texture.get_width();   // Frame width in pixels
  int height = texture.get_height(); // Frame height in pixels

  // Normals to Texture Coordinates conversion
  int x_value = min(max(int(Texture_XY.u * width + .5f), 0), width - 1);
  int y_value = min(max(int(Texture_XY.v * height + .5f), 0), height - 1);

  int bytes = x_value * texture.get_bytes_per_pixel();   // Get # of bytes per pixel
  int strides = y_value * texture.get_stride_in_bytes(); // Get line width in bytes
  int Text_Index = (bytes + strides);

  const auto New_Texture = reinterpret_cast<const uint8_t *>(texture.get_data());

  // RGB components to save in tuple
  int NT1 = New_Texture[Text_Index];
  int NT2 = New_Texture[Text_Index + 1];
  int NT3 = New_Texture[Text_Index + 2];

  return std::tuple<int, int, int>(NT1, NT2, NT3);
}

//===================================================
//  PCL_Conversion
// - Function is utilized to fill a point cloud
//  object with depth and RGB data from a single
//  frame captured using the Realsense.
//===================================================
pcl::PointCloud<pcl::PointXYZRGB>::Ptr PCL_Conversion(const rs2::points &points, const rs2::video_frame &color)
{
  // Object Declaration (Point Cloud)
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);

  // Declare Tuple for RGB value Storage (<t0>, <t1>, <t2>)
  std::tuple<uint8_t, uint8_t, uint8_t> RGB_Color;

  //================================
  // PCL Cloud Object Configuration
  //================================
  // Convert data captured from Realsense camera to Point Cloud
  auto sp = points.get_profile().as<rs2::video_stream_profile>();

  cloud->width = static_cast<uint32_t>(sp.width());
  cloud->height = static_cast<uint32_t>(sp.height());
  cloud->is_dense = false;
  cloud->points.resize(points.size());

  auto Texture_Coord = points.get_texture_coordinates();
  auto Vertex = points.get_vertices();

  // Iterating through all points and setting XYZ coordinates
  // and RGB values
  for (int i = 0; i < points.size(); i++)
  {
    //===================================
    // Mapping Depth Coordinates
    // - Depth data stored as XYZ values
    //===================================
    cloud->points[i].x = Vertex[i].x;
    cloud->points[i].y = Vertex[i].y;
    cloud->points[i].z = Vertex[i].z;

    // Obtain color texture for specific point
    RGB_Color = RGB_Texture(color, Texture_Coord[i]);

    // Mapping Color (BGR due to Camera Model)
    cloud->points[i].r = get<2>(RGB_Color); // Reference tuple<2>
    cloud->points[i].g = get<1>(RGB_Color); // Reference tuple<1>
    cloud->points[i].b = get<0>(RGB_Color); // Reference tuple<0>
  }

  return cloud; // PCL RGB Point Cloud generated
}

pcl::PointCloud<pcl::PointXYZRGB>::Ptr rotatePCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGCloud, float x, float y, float z)
{
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr transCloud(new pcl::PointCloud<pcl::PointXYZRGB>);

  Eigen::Affine3f transformer = Eigen::Affine3f::Identity();

  // Rotate the cloud with             rotation on axis
  transformer.rotate(Eigen::AngleAxisf(x, Eigen::Vector3f::UnitX()));
  transformer.rotate(Eigen::AngleAxisf(y, Eigen::Vector3f::UnitY()));
  transformer.rotate(Eigen::AngleAxisf(z, Eigen::Vector3f::UnitZ()));
  // Rotate cloud
  pcl::transformPointCloud(*OGCloud, *transCloud, transformer);
  return transCloud;
}

pcl::PointCloud<pcl::PointXYZRGB>::Ptr movePCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGcloud, float x, float y, float z)
{
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr transCloud(new pcl::PointCloud<pcl::PointXYZRGB>);
  Eigen::Affine3f transformer = Eigen::Affine3f::Identity();
  // Move cloud x y z
  transformer.translation() << x, y, z;

  // Rotate cloud
  pcl::transformPointCloud(*OGcloud, *transCloud, transformer);
  return transCloud;
}

pcl::PointCloud<pcl::PointXYZ>::Ptr filterPCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGCloud,
                                              float x, float x1, float y, float y1, float z, float z1)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr filterCloud(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::copyPointCloud(*OGCloud, *filterCloud);
  pcl::PassThrough<pcl::PointXYZ> pass;
  pass.setInputCloud(filterCloud);
  pass.setFilterFieldName("x");
  pass.setFilterLimits(x, x1);
  pass.setFilterFieldName("y");
  pass.setFilterLimits(y, y1);
  pass.setFilterFieldName("z");
  pass.setFilterLimits(z, z1);
  pass.filter(*filterCloud);

  return filterCloud;
}

int main()
try
{
  //====================
  // Object Declaration
  //====================
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr currentFrame(new pcl::PointCloud<pcl::PointXYZRGB>);
  boost::shared_ptr<pcl::visualization::PCLVisualizer> openCloud;
  //pcl::PointCloud<pcl::PointXYZRGB>::Ptr prevFrame(new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr transCloud(new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr filterCloud(new pcl::PointCloud<pcl::PointXYZ>);

  rs2::pointcloud pc;
  rs2::pipeline pipe;
  rs2::config cfg;

  //======================
  // Stream configuration with parameters resolved internally. See enable_stream() overloads for extended usage
  //======================
  cfg.enable_stream(RS2_STREAM_COLOR);
  cfg.enable_stream(RS2_STREAM_INFRARED);
  cfg.enable_stream(RS2_STREAM_DEPTH);

  rs2::pipeline_profile selection = pipe.start(cfg);

  rs2::device selected_device = selection.get_device();
  auto depth_sensor = selected_device.first<rs2::depth_sensor>();

  if (depth_sensor.supports(RS2_OPTION_EMITTER_ENABLED))
  {
    depth_sensor.set_option(RS2_OPTION_EMITTER_ENABLED, 1.f); // Enable emitter
    pipe.wait_for_frames();
    depth_sensor.set_option(RS2_OPTION_EMITTER_ENABLED, 0.f); // Disable emitter
  }

  if (depth_sensor.supports(RS2_OPTION_LASER_POWER))
  {
    // Query min and max values:
    auto range = depth_sensor.get_option_range(RS2_OPTION_LASER_POWER);
    depth_sensor.set_option(RS2_OPTION_LASER_POWER, range.max); // Set max power
    sleep(1);
    depth_sensor.set_option(RS2_OPTION_LASER_POWER, 0.f); // Disable laser
  }

  for (int i = 0; i < INT_MAX; i++)
  {
    // Capture a single frame and obtain depth + RGB values from it
    auto frames = pipe.wait_for_frames();
    auto depth = frames.get_depth_frame();
    auto RGB = frames.get_color_frame();

    // Map Color texture to each point
    pc.map_to(RGB);

    // Generate Point Cloud
    auto points = pc.calculate(depth);

    // Convert generated Point Cloud to PCL Formatting
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud = PCL_Conversion(points, RGB);

    currentFrame = cloud;

    transCloud = rotatePCL(cloud, 1.0, 0.7, 0.0);
    transCloud = movePCL(transCloud, -1.0, 0.1, 0.1);
    filterCloud = filterPCL(transCloud, -1, 1, -1, 1, -1, 1.5);

    viewer->setBackgroundColor(0, 0, 0);
    // Add generated point cloud and identify with string "Cloud"
    viewer->addPointCloud<pcl::PointXYZRGB>(cloud, "Cloud");
    // Default size for rendered points
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "Cloud");
    // Viewer Properties
    viewer->initCameraParameters();

    viewer->updatePointCloud<pcl::PointXYZRGB>(cloud, "Cloud");
    viewer->spinOnce(100);

    transViewer->setBackgroundColor(0, 0, 0);
    // Add generated point cloud and identify with string "Cloud"
    transViewer->addPointCloud<pcl::PointXYZRGB>(transCloud, "Cloud");
    // Default size for rendered points
    transViewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "Cloud");
    // Viewer Properties
    transViewer->initCameraParameters();
    transViewer->addCoordinateSystem();

    transViewer->updatePointCloud<pcl::PointXYZRGB>(transCloud, "Cloud");
    transViewer->spinOnce(100);

    filterdViewer->setBackgroundColor(0, 0, 0);
    // Add generated point cloud and identify with string "Cloud"
    filterdViewer->addPointCloud<pcl::PointXYZ>(filterCloud, "Cloud");
    // Default size for rendered points
    filterdViewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "Cloud");
    // Viewer Properties
    filterdViewer->initCameraParameters();

    filterdViewer->updatePointCloud<pcl::PointXYZ>(filterCloud, "Cloud");
    filterdViewer->spinOnce(100);

    while(true)
    {
      viewer->updatePointCloud<pcl::PointXYZRGB>(cloud, "Cloud");
      viewer->spinOnce(100);
      transViewer->updatePointCloud<pcl::PointXYZRGB>(transCloud, "Cloud");
      transViewer->spinOnce(100);
      filterdViewer->updatePointCloud<pcl::PointXYZ>(filterCloud, "Cloud");
      filterdViewer->spinOnce(100);
    }
  }

  cout << "Exiting Program... " << endl;
  return EXIT_SUCCESS;
}
catch (const rs2::error &e)
{
  std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
  return EXIT_FAILURE;
}
catch (const std::exception &e)
{
  std::cerr << e.what() << std::endl;
  return EXIT_FAILURE;
}
