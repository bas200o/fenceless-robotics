#include "../include/Controller3D.hpp"

Controller3D::Controller3D(/* args */)
{
}

Controller3D::~Controller3D(){

}

void Controller3D::CreateNewInformation(){
    Information3D Info3D;
    Information3D temp1;
    Information3D temp2;
    Information3D temp3;
    printf("Creating first info \n");
    //make sure the first is the newest info
    temp2 = lastInfo[0];
    lastInfo[0] = Info3D;
    cout << sizeof(lastInfo)/sizeof(lastInfo[0]) << endl;
    for(int i = 1; i < sizeof(lastInfo)/sizeof(lastInfo[0]); i++){
        if(temp2.GetPointCloud().size() > 0){
            temp1 = lastInfo[i];
            lastInfo[i] = temp2;
            temp2 = temp1;
        }
    }
    CameraConnector *camCon = camCon->getInstance();
    std::vector<pcl::PointCloud<pcl::PointXYZRGB> > temp = camCon->retrievePointClouds();
    lastInfo[0].AddPointClouds(camCon->retrievePointClouds());
    printf("Created first info \n");
    return;
    

}

void Controller3D::DetectObjects(int pCloud){
    printf("Detecting \n");

    if(pCloud >= 5){
        return;
    };
    if(lastInfo[pCloud].getObjects().size() > 0){
        return;
    }
    pcl::PointCloud<pcl::PointXYZRGB> tempCloud(lastInfo[pCloud].GetPointCloud());
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_f(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    *cloud = tempCloud;

    pcl::VoxelGrid<pcl::PointXYZRGB> vg;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZRGB>);
    vg.setInputCloud(cloud);
    vg.setLeafSize(0.01f, 0.01f, 0.01f);
    vg.filter(*cloud_filtered);

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
            lastInfo[pCloud].InsertObject(*cloud_cluster);
    }
    return;
}

void Controller3D::RemoveBackground(int pCloud){
    return;
}

void Controller3D::CombinePointClouds(int pCloud){
    return;
}

void Controller3D::CalculateSpeed(int pCloud){
    return;
}
//