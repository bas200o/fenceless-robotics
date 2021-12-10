#include <librealsense2/rs.hpp>
#include <librealsense2/hpp/rs_internal.hpp>
#include <iostream>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>

#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QTableView>
#include <QTableWidget>


// -----------

class Window : public QWidget
{
    public:
        explicit Window(QWidget *parent = 0);

        // int addObject(object o);
        // void updateObject(int id, object o);
        void removeObject(int id);


    private:
        QWidget *panel_2dview;
        QWidget *panel_3dview;
        QWidget *panel_statistics;
        QTableWidget *panel_objecttable;

        QGridLayout *layout;

        QStringList tableHeaders = { 
            "ID", 
            "Tijd in beeld", 
            "PosX", 
            "PosY", 
            "PosZ", 
            "Formaat", 
            "Richting", 
            "Versnelling" };

        QTableWidgetItem *objects[8][5];

};

Window::Window(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1240, 830);

    panel_2dview = new QPushButton(" 2D View ");
    panel_3dview = new QPushButton(" 3D View ");
    panel_statistics = new QPushButton("Stats");
    panel_objecttable = new QTableWidget(this);

    panel_2dview->setFixedSize(400, 400);
    panel_3dview->setFixedSize(400, 400);
    panel_statistics->setFixedSize(400, 400);
    panel_objecttable->setFixedSize(1220, 400);

    panel_objecttable->setRowCount(5);
    panel_objecttable->setColumnCount(8);
    panel_objecttable->setHorizontalHeaderLabels(tableHeaders);

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 5; j++)
            objects[i][j] = new QTableWidgetItem(tr("%1").arg((i+1)*(j+1)));

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 5; j++)
            panel_objecttable->setItem(j, i, objects[i][j]);
    

    layout = new QGridLayout(this);
    layout->addWidget(panel_2dview, 0, 0);
    layout->addWidget(panel_3dview, 0, 1);
    layout->addWidget(panel_statistics, 0, 2);
    layout->addWidget(panel_objecttable, 1, 0, 1, 3);
    
}

// -----------


int main(int argc, char **argv)
{
    rs2::context ctx;

    std::cout << "hello from librealsense - " << RS2_API_VERSION_STR << std::endl;
    std::cout << "You have " << ctx.query_devices().size() << " RealSense devices connected" << std::endl;

    pcl::PointCloud<pcl::PointXYZRGB> cloud;

    //fill coud with data,

    QApplication app (argc, argv);
    Window window;
    window.show();



 return app.exec();


    cloud.width = 100;
    cloud.height = 1;
    cloud.is_dense = false;
    cloud.points.resize(cloud.width * cloud.height);

    for (size_t i = 0; i < cloud.points.size(); i++) {
        cloud.points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
        cloud.points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
        cloud.points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
        cloud.points[i].r = 255 * rand() / (RAND_MAX + 1.0f);
        cloud.points[i].g = 255 * rand() / (RAND_MAX + 1.0f);
        cloud.points[i].b = 255 * rand() / (RAND_MAX + 1.0f);
    }


    pcl::io::savePCDFileASCII("test_pcd.pcd", cloud);
    std::cerr << "Saved " << cloud.points.size() << " data points to test_pcd.pcd." << std::endl;

//     for (size_t i = 0; i < cloud.points.size(); i++) {
//         std::cerr << "      " << cloud.points[i].x << " " << cloud.points[i].y << " " << cloud.points[i].z << std::endl;
//     }

//     pcl::PointCloud<pcl::PointXYZ>::Ptr hey;
//     pcl::io::loadPCDFile("test_pcd.pcd", *hey);
//    //... populate cloud

//    pcl::visualization::CloudViewer viewer ("Simple Cloud Viewer");
//    viewer.showCloud(hey );
//    while (!viewer.wasStopped ())
//    {
//    }



    return 0;
}

// #include <pcl/visualization/cloud_viewer.h>
// #include <iostream>
// #include <pcl/io/io.h>
// #include <pcl/io/pcd_io.h>
    
// int user_data;
    
// void 
// viewerOneOff (pcl::visualization::PCLVisualizer& viewer)
// {
//     viewer.setBackgroundColor (1.0, 0.5, 1.0);
//     pcl::PointXYZ o;
//     o.x = 1.0;
//     o.y = 0;
//     o.z = 0;
//     viewer.addSphere (o, 0.25, "sphere", 0);
//     std::cout << "i only run once" << std::endl;
    
// }
    
// void 
// viewerPsycho (pcl::visualization::PCLVisualizer& viewer)
// {
//     static unsigned count = 0;
//     std::stringstream ss;
//     ss << "Once per viewer loop: " << count++;
//     viewer.removeShape ("text", 0);
//     viewer.addText (ss.str(), 200, 300, "text", 0);
    
//     //FIXME: possible race condition here:
//     user_data++;
// }
    
// int 
// main ()
// {
//     pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGBA>);
//     pcl::io::loadPCDFile ("my_point_cloud.pcd", *cloud);
    
//     pcl::visualization::CloudViewer viewer("Cloud Viewer");
    
//     //blocks until the cloud is actually rendered
//     viewer.showCloud(cloud);
    
//     //use the following functions to get access to the underlying more advanced/powerful
//     //PCLVisualizer
    
//     //This will only get called once
//     viewer.runOnVisualizationThreadOnce (viewerOneOff);
    
//     //This will get called once per visualization iteration
//     viewer.runOnVisualizationThread (viewerPsycho);
//     while (!viewer.wasStopped ())
//     {
//     //you can also do cool processing here
//     //FIXME: Note that this is running in a separate thread from viewerPsycho
//     //and you should guard against race conditions yourself...
//     user_data++;
//     }
//     return 0;
// }