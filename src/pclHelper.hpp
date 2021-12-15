#include "pcl/common/common_headers.h"
#include "pcl/io/obj_io.h"
#include "pcl/io/pcd_io.h"
#include "pcl/io/vtk_lib_io.h"
#include "pcl/visualization/pcl_visualizer.h"

namespace pclHelperFunctions {
    class pclHelper {
        public:
            void showPCL(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
            pcl::PointCloud<pcl::PointXYZ>::Ptr generatePCL();

            pcl::PointCloud<pcl::PointXYZ>::Ptr loadPCL(std::string file_path);

            pcl::PointCloud<pcl::PointXYZ>::Ptr combinePointClouds(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud1, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2);
            
    };
}