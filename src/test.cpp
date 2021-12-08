#include "pcl/common/common_headers.h"
#include "pcl/io/obj_io.h"
#include "pcl/io/pcd_io.h"
#include "pcl/io/vtk_lib_io.h"
#include "pcl/visualization/pcl_visualizer.h"


int main()
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    if (pcl::io::loadPCDFile("test_pcd.pcd", *cloud) == -1) //* load the file
  {
    PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
    return (-1);
  }
 
  // pcl::io::loadPCDFile ("test_pcd.pcd", *cloud);
  // pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  // cloud->width=10;
  // cloud->height=2;
  // cloud->is_dense = false;
  // cloud->points.resize(cloud->width * cloud->height);

  // for (size_t i = 0; i < cloud->points.size(); ++i)
  // {
  //   cloud->points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
  //   cloud->points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
  //   cloud->points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
  // }

  pcl::visualization::PCLVisualizer viewer;
  viewer.addPointCloud(cloud);
  viewer.spin();
  
  return 0;
}
