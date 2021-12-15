#include "pcl/common/common_headers.h"
#include "pcl/io/obj_io.h"
#include "pcl/io/pcd_io.h"
#include "pcl/io/vtk_lib_io.h"
#include "pcl/visualization/pcl_visualizer.h"

#include <librealsense2/rs.hpp>

#include "pclHelper.hpp"

using namespace pclHelperFunctions;

int main()
{
  pclHelper helper;
 
    // If you dont have a test pcd file use this to generate one.
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud = helper.generatePCL();

  for (int i = 0; i < 10000; i++) {
    cloud = helper.combinePointClouds(cloud, helper.generatePCL());
  }
  std::cout << cloud->size() << std::endl;
  helper.showPCL(cloud);

  
  return 0;
}