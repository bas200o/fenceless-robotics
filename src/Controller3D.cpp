#include "../include/Controller3D.hpp"
// pcl transformation
#include <pcl/common/transforms.h>
// pcl filter
#include <pcl/filters/passthrough.h>
#include "../include/SettingSingleton.hpp"
#include <iostream>
#include <chrono>
#include <ctime>

Controller3D::Controller3D(/* args */)
{
    pcl::visualization::PCLVisualizer::Ptr viewerTemp(new pcl::visualization::PCLVisualizer("3D Viewer"));
    viewer = viewerTemp;
    viewer->setBackgroundColor(0, 0, 0);
    viewer->initCameraParameters();
    viewer->addCoordinateSystem();
    viewer->setWindowName("config sceen");
}

Controller3D::~Controller3D()
{
}

/**
 * Creates an array of information3d objects
 * @return void saves to lastinfo array
 */
void Controller3D::CreateNewInformation()
{
    Information3D Info3D;
    Information3D temp1;
    Information3D temp2;
    Information3D temp3;
    //make sure the first is the newest info
    temp2 = lastInfo[0];
    lastInfo[0] = Info3D;
    //cout << sizeof(lastInfo) / sizeof(lastInfo[0]) << endl;
    for (int i = 1; i < sizeof(lastInfo) / sizeof(lastInfo[0]); i++)
    {
        if (temp2.getPointCloud().size() > 0)
        {
            temp1 = lastInfo[i];
            lastInfo[i] = temp2;
            temp2 = temp1;
        }
    }
    CameraConnector *camCon = camCon->getInstance();
    lastInfo[0].AddPointClouds(camCon->retrievePointClouds());
    lastInfo[0].setTimeStamp(camCon->getLastTimeStamp());
}

/**
 * Detects objects and stores information in Information3d object
 * @param pInfo The information3d object to retrieve and store data.
 */
void Controller3D::DetectObjects(int pInfo)
{
    cout<<"detecting in pointcloud of size: "<<lastInfo[pInfo].getPointCloud().points.size()<<endl;
    //lastInfo[pInfo].

    if (pInfo >= 5)
    {
        return;
    };
    if (lastInfo[pInfo].getObjects().size() > 0)
    {
        return;
    }
    pcl::PointCloud<pcl::PointXYZRGB> tempInfo(lastInfo[pInfo].getPointCloud());
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_f(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    *cloud = tempInfo;

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
    seg.setDistanceThreshold(0.01);

    int nr_points = (int)cloud_filtered->size();
    while (cloud_filtered->size() > 1 * nr_points)
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
    ec.setClusterTolerance(0.07); // 10cm
    ec.setMinClusterSize(25);
    ec.setMaxClusterSize(25000);
    ec.setSearchMethod(tree);
    ec.setInputCloud(cloud_filtered);
    ec.extract(cluster_indices);


    // pcl::PointCloud<pcl::PointXYZRGB>::Ptr full(new pcl::PointCloud<pcl::PointXYZRGB>());
    viewer->removeAllPointClouds();
    int j = 0;
    for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin(); it != cluster_indices.end(); ++it)
    {
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_cluster(new pcl::PointCloud<pcl::PointXYZRGB>);
        for (const auto &idx : it->indices)
            cloud_cluster->push_back((*cloud_filtered)[idx]); //*
        cloud_cluster->width = cloud_cluster->size();
        cloud_cluster->height = 1;
        cloud_cluster->is_dense = true;
        lastInfo[pInfo].InsertObject(*cloud_cluster);

            //TEMPORARY CODE TO DISPLAY POINTCLOUD -> ENDS AT <END TEMPORARY> COMMENT
        for (size_t i = 0; i < cloud_cluster->points.size(); i++)
        {
            switch (j)
            {
            case 0:
                cloud_cluster->points[i].r = 0;
                cloud_cluster->points[i].g = 255;
                cloud_cluster->points[i].b = 0; 
                break;
            case 1:
                cloud_cluster->points[i].r = 255;
                cloud_cluster->points[i].g = 0;
                cloud_cluster->points[i].b = 0; 
                break;
            case 2:
                cloud_cluster->points[i].g = 0;
                cloud_cluster->points[i].r = 0;
                cloud_cluster->points[i].b = 255;
                break;
            default:
                break;
            }
        }
        viewer->addPointCloud(cloud_cluster, "hey" + j);
        j++;
    }
    std::cout << "number of found objects: "<< j <<std::endl;
    viewer->spinOnce(100, true);
}

/**
 * Method processes pointclouds to rotate move combine and filter.
 * @return void data stored in information3d object
 */
void Controller3D::ProccesPointcloud()
{
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr full(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);

    auto clouds = lastInfo[0].getPointClouds();
    *cloud = clouds.at(0);

    SettingSingleton* settings = SettingSingleton::getInstance();

    for (size_t i = 0; i < clouds.size(); i++) {
        if (settings->getVisable(i)) {
            *cloud = clouds.at(i);
            cloud = rotatePCL(cloud, settings->getRotate(i));
            cloud = rotatePCL(cloud, settings->getRotate2(i));
            cloud = movePCL(cloud, settings->getMove(i));
            cloud = filterPCL(cloud, settings->getFilter(i));
            *full += *cloud;
        }
        
    }
    lastInfo[0].AddFullPointCloud(*full);

    
    return;
}

/**
 * Combines pointclouds from a information 3d object
 * @param pInfo Information3d object to combine pointclouds of.
 * @return Combined pointclouds
 */
pcl::PointCloud<pcl::PointXYZRGB>::Ptr Controller3D::CombinePointClouds(int pInfo)
{
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr full;
    for (auto &&pointcloud : lastInfo[pInfo].getPointClouds())
    {
        *full += pointcloud;
    }
    return full;
}

/**
 * Calculates speed of objects in pointcloud
 * @return void method saves speed in the information3d object
 */
void Controller3D::CalculateSpeed(){
    Information3D previous = lastInfo[3];
    for(int i = 0; i < lastInfo[0].objects.size(); i++){
        double speed = -1;
        float dist;
        for(int j = 0; j < previous.objects.size() ; j++){
                if(previous.objects[j].getIdentificationNumber() == lastInfo[0].objects[i].getIdentificationNumber()){
                    dist = euclideanDistance(lastInfo[0].objects[i].getLocation(), previous.objects[j].getLocation());
                    //cout << " dis " << dist << endl;
                    //cout << " time " << (lastInfo[0].getTimeStamp() - previous.getTimeStamp())/1000 << endl;
                    speed = dist / ((lastInfo[0].getTimeStamp() - previous.getTimeStamp())/1000);
                }    
        }
        speed = speed < 0.1 ? 0 : speed;
        lastInfo[0].objects[i].setSpeed(speed);
        //cout << "speed set: " << speed << endl;
    }
}

void Controller3D::calculateDirection(){
    Information3D previous = lastInfo[3];
    for(int i = 0; i < lastInfo[0].objects.size(); i++){
        double angle = -1;
        float dist;
        for(int j = 0; j < previous.objects.size() ; j++){
                if(previous.objects[j].getIdentificationNumber() == lastInfo[0].objects[i].getIdentificationNumber()){
                    std::tuple<float, float, float> pCent = previous.objects[j].getCenterMass();
                    std::tuple<float, float, float> lCent =lastInfo[0].objects[i].getCenterMass();
                    float p1z = get<2>(pCent);
                    float p2z = get<2>(lCent);
                    float p1y = get<1>(pCent);
                    float p2y = get<1>(lCent);
                    float p1x = get<0>(pCent);
                    float p2x = get<0>(lCent);
                    float deltaZ = p2z - p1z;
                    float deltaY = p2y - p1y;
                    float deltaX = p2x - p1x; //Vector 2 is now relative to origin, the angle is the same, we have just transformed it to use the origin.

                    float vertAngleInDegrees;
                    float horAngleInDegrees;

                    if(-0.01 > deltaX < 0.01 && -0.01 > deltaZ < 0.01){
                        horAngleInDegrees = 0;
                        cout << "wtf" << endl;
                    }
                    else{
                    horAngleInDegrees = atan2(deltaX, deltaZ) * 180 / 3.141;
                    }

                    float deltaXZ = sqrt((deltaX * deltaX) + (deltaZ*deltaZ));
                    if(-0.01 > deltaX < 0.01 && -0.01 >deltaY < 0.01){
                        vertAngleInDegrees = 0;
                    }
                    else{
                        vertAngleInDegrees = atan2(deltaY, deltaXZ) * 180 / 3.141;
                    }

                    cout << "angle set hor: " << deltaX << endl;
                    cout << "angle set ver: " << deltaZ << endl;

                    lastInfo[0].objects[i].setDirectionHor(horAngleInDegrees);
                    lastInfo[0].objects[i].setDirectionVer(vertAngleInDegrees);
                    //vertAngleInDegrees *= -1; // Y axis is inverted in computer windows, Y goes down, so invert the angle.
                    //Eigen::Vector3f e_v3f_pt = lastInfo[0].objects[i].getLocation().getVector3fMap();
                    //Eigen::Vector3f e_v3f_pt2 = previous.objects[j].getLocation().getVector3fMap();
                    //angle = pcl::getAngle3D(e_v3f_pt2, e_v3f_pt, false);
                }    
        }

        //cout << "angle set: " << horAngleInDegrees << endl;

    }
}

void Controller3D::assignIdentification(){
    Information3D previous;
    Information3D current;
    previous = lastInfo[1];
    current = lastInfo[0];
    
    for(int i = 0; i < current.objects.size(); i++){
        float dist;
        float closestSize = FLT_MAX;
        float shortestDist = FLT_MAX;
        FoundObject closestSimilarObject;
        FoundObject object = lastInfo[0].objects[i];
        std::vector<FoundObject> potentialObjects;
        FoundObject movedObject;

        for(FoundObject oldObj: previous.getObjects()){
            dist = euclideanDistance(object.getLocation(), oldObj.getLocation());
            if (dist < shortestDist && dist < 0.30)
            {
                potentialObjects.push_back(oldObj);
            }
        }
        
        for(FoundObject potObj: potentialObjects){
            float tempSize = abs(potObj.getSize() - object.getSize());
            if(closestSize > tempSize){
                closestSize = tempSize;
                closestSimilarObject = potObj;
            }
        }

        if(closestSimilarObject.getSize() != 0){
            lastInfo[0].objects[i].setIdentificationNumber(closestSimilarObject.getIdentificationNumber());
        }

        else{
            lastInfo[0].objects[i].setIdentificationNumber(identificationNumber);
            identificationNumber++;
        }
    }
}

/**
 * rotates the pointcloud on xyz axis from SettingSingleton
 * @param OGCloud The original pointcloud
 * @return The rotated pointcloud
 */
pcl::PointCloud<pcl::PointXYZRGB>::Ptr Controller3D::rotatePCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGCloud)
{
    SettingSingleton *ds = ds->getInstance();
    struct rotationSettings rs = ds->getRotate(0);
    return Controller3D::rotatePCL(OGCloud, rs.x, rs.y, rs.z);
}

/**
 * Rotates the pointcloud with a rotationSettings struct
 * @param OGCloud The original pointcloud
 * @param rs The rotationsSettings struct
 * @return The rotated pointcloud
 */
pcl::PointCloud<pcl::PointXYZRGB>::Ptr Controller3D::rotatePCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGCloud, rotationSettings rs)
{
    return Controller3D::rotatePCL(OGCloud, rs.x, rs.y, rs.z);
}

/**
 * Rotates the pointcloud around the XYZ axis
 * @param OGCloud The original pointcloud
 * @param x Rotate on x axis
 * @param y Rotate on y axis
 * @param z Rotate on z axis
 * @return The rotated pointcloud
 */
pcl::PointCloud<pcl::PointXYZRGB>::Ptr Controller3D::rotatePCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGCloud, float x, float y, float z)
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

/**
 * Moves the pointcloud with settings from the SettingSingleton
 * @param OGcloud The original pointcloud
 * @return The moved pointcloud
 */
pcl::PointCloud<pcl::PointXYZRGB>::Ptr Controller3D::movePCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGcloud)
{
    SettingSingleton *ds = ds->getInstance();
    struct moveSettings ms = ds->getMove(0);
    return Controller3D::movePCL(OGcloud, ms.x, ms.y, ms.z);
}

/**
 * Moves the Pointcloud with the settings from the moveSettings struct
 * @param OGCloud the original pointlcoud
 * @param ms The move settings for the pointcloud
 * @return The moved pointcloud
 */
pcl::PointCloud<pcl::PointXYZRGB>::Ptr Controller3D::movePCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGcloud, moveSettings ms)
{
    return Controller3D::movePCL(OGcloud, ms.x, ms.y, ms.z);
}

/**
 * @param OGCloud The original pointcloud
 * @param x move the x pos
 * @param y move the y pos
 * @oaram z move the z pos
 * @return The moved pointcloud
 */
pcl::PointCloud<pcl::PointXYZRGB>::Ptr Controller3D::movePCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGcloud, float x, float y, float z)
{

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr transCloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    Eigen::Affine3f transformer = Eigen::Affine3f::Identity();
    // Move cloud x y z
    transformer.translation() << x, y, z;

    // Rotate cloud
    pcl::transformPointCloud(*OGcloud, *transCloud, transformer);
    return transCloud;
}

/**
 * Filters point cloud on basis of SettingSingleton
 * @param OGCloud The unfilterd pointcloud RGB
 * @return The filterd pointcloud RGB
 */
pcl::PointCloud<pcl::PointXYZRGB>::Ptr Controller3D::filterPCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGCloud)
{
    SettingSingleton *ds = ds->getInstance();
    struct filterSettings rs = ds->getFilter(0);
    
    return Controller3D::filterPCL(OGCloud, rs.x, rs.x1, rs.y, rs.y1, rs.z, rs.z1);
}

// Gets xyz from singleton
pcl::PointCloud<pcl::PointXYZRGB>::Ptr Controller3D::filterPCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGCloud, filterSettings fs)
{   
    return Controller3D::filterPCL(OGCloud, fs.x, fs.x1, fs.y, fs.y1, fs.z, fs.z1);
}

/**
 * Filters pointcloud to cut out points that exceed the xyz values
 * @param OGCloud the original pointcloud
 * @param x X keep start
 * @param x1 X keep end
 * @param y Y keep start
 * @param y1 Y keep end
 * @param z Z keep start
 * @param z1 Z keep end
 * @return pointcloud xyzrgb filterd
 */
pcl::PointCloud<pcl::PointXYZRGB>::Ptr Controller3D::filterPCL(pcl::PointCloud<pcl::PointXYZRGB>::Ptr OGCloud,
                                                               float x, float x1, float y, float y1, float z, float z1)
{   
    pcl::PointCloud<pcl::PointXYZRGB> filteredCloud;
    filteredCloud.reserve(OGCloud->points.size());
    
    for (pcl::PointCloud<pcl::PointXYZRGB>::iterator it = OGCloud->begin(); it != OGCloud->end(); it++)
    {
        if (!(  
                it->x < x || it->x > x1 ||
                it->y < y || it->y > y1 ||
                it->z < z || it->z > z1
            ))
        {
            filteredCloud.push_back(*it);
        }
    }

    *OGCloud = std::move(filteredCloud);
    return OGCloud;
}

void Controller3D::pushUIData(){
    GUIData::getInstance()->setObjects(lastInfo[0]);
}

void Controller3D::configure(){
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr full(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);

    auto clouds = lastInfo[0].getPointClouds();
    *cloud = clouds.at(0);

    SettingSingleton* settings = SettingSingleton::getInstance();

    for (size_t i = 0; i < clouds.size(); i++) {
        if (settings->getVisable(i)) {
            *cloud = clouds.at(i);
            for (size_t y = 0; y < cloud->points.size(); y++)
            {
                cloud->points[y].r = settings->getRgb(i).r;
                cloud->points[y].g = settings->getRgb(i).g;
                cloud->points[y].b = settings->getRgb(i).b;
            }
            cloud = rotatePCL(cloud, settings->getRotate(i));
            cloud = rotatePCL(cloud, settings->getRotate2(i));
            cloud = movePCL(cloud, settings->getMove(i));
            cloud = filterPCL(cloud, settings->getFilter(i));
            *full += *cloud;
        }
        
    }



    viewer->removeAllPointClouds();
    viewer->addPointCloud(full);
    viewer->spinOnce(5);
}