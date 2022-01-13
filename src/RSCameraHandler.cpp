#include "../include/RSCameraHandler.hpp"


RSCameraHandler::RSCameraHandler(/* args */)
{
    config.enable_stream(RS2_STREAM_COLOR);
    config.enable_stream(RS2_STREAM_INFRARED);
    config.enable_stream(RS2_STREAM_DEPTH);
    connectCamera();
}


RSCameraHandler::~RSCameraHandler()
{
    if (pipeRunning) {
        CameraConnector::getInstance()->remConnectedRSCamera(pipe.get_active_profile().get_device().get_info(RS2_CAMERA_INFO_SERIAL_NUMBER));
        pipe.stop();
    }
}

void RSCameraHandler::setLatestCloud(pcl::PointCloud<pcl::PointXYZ> pointCloud) {
        CameraHandler::latestCloud_mtx.lock();
        CameraHandler::latestCloud = pointCloud;
        CameraHandler::latestCloud_mtx.unlock();
}

void RSCameraHandler::setLatestCloud(pcl::PointCloud<pcl::PointXYZRGB> pointCloud) {
        CameraHandler::latestRGBCloud_mtx.lock();
        CameraHandler::latestRGBCloud = pointCloud;
        CameraHandler::latestRGBCloud_mtx.unlock();
}

cv::Mat RSCameraHandler::convertToMatrix()
{
    //return has to be changed, this is placeholder    
    return cv::Mat();
}

std::tuple<int, int, int> RGB_Texture(rs2::video_frame texture, rs2::texture_coordinate Texture_XY)
{
    // Get Width and Height coordinates of texture
    int width  = texture.get_width();  // Frame width in pixels
    int height = texture.get_height(); // Frame height in pixels
    
    // Normals to Texture Coordinates conversion
    int x_value = min(max(int(Texture_XY.u * width  + .5f), 0), width - 1);
    int y_value = min(max(int(Texture_XY.v * height + .5f), 0), height - 1);

    int bytes = x_value * texture.get_bytes_per_pixel();   // Get # of bytes per pixel
    int strides = y_value * texture.get_stride_in_bytes(); // Get line width in bytes
    int Text_Index =  (bytes + strides);

    const auto New_Texture = reinterpret_cast<const uint8_t*>(texture.get_data());
    
    // RGB components to save in tuple
    int NT1 = New_Texture[Text_Index];
    int NT2 = New_Texture[Text_Index + 1];
    int NT3 = New_Texture[Text_Index + 2];

    return std::tuple<int, int, int>(NT1, NT2, NT3);
}

std::tuple<pcl::PointCloud<pcl::PointXYZRGB>, pcl::PointCloud<pcl::PointXYZ>> RSCameraHandler::convertBothPCL() {

    rs2::pointcloud pc;
    RSCameraHandler::frames = pipe.wait_for_frames();
    rs2::depth_frame depth = frames.get_depth_frame();

    auto RGB = frames.get_color_frame();


    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::PointCloud<pcl::PointXYZRGB> cloudRGB;

    std::tuple<uint8_t, uint8_t, uint8_t> RGB_Color;

    //================================
    // PCL Cloud Object Configuration
    //================================
    // Convert data captured from Realsense camera to Point Cloud
    auto sp = RSCameraHandler::points.get_profile().as<rs2::video_stream_profile>();
    
    cloud.width  = static_cast<uint32_t>( sp.width()  );   
    cloud.height = static_cast<uint32_t>( sp.height() );
    cloud.is_dense = false;
    cloud.points.resize(RSCameraHandler::points.size() );

    cloudRGB.width  = static_cast<uint32_t>( sp.width()  );   
    cloudRGB.height = static_cast<uint32_t>( sp.height() );
    cloudRGB.is_dense = false;
    cloudRGB.points.resize(RSCameraHandler::points.size() );

    auto Texture_Coord = RSCameraHandler::points.get_texture_coordinates();
    auto Vertex = RSCameraHandler::points.get_vertices();

    // Iterating through all points and setting XYZ coordinates
    // and RGB values
    for (int i = 0; i < RSCameraHandler::points.size(); i++)
    {   
        //===================================
        // Mapping Depth Coordinates
        // - Depth data stored as XYZ values
        //===================================
        cloud.points[i].x = Vertex[i].x;
        cloud.points[i].y = Vertex[i].y;
        cloud.points[i].z = Vertex[i].z;

        cloudRGB.points[i].x = Vertex[i].x;
        cloudRGB.points[i].y = Vertex[i].y;
        cloudRGB.points[i].z = Vertex[i].z;

        // Obtain color texture for specific point
        RGB_Color = RGB_Texture(frames.get_color_frame(), Texture_Coord[i]);

        // Mapping Color (BGR due to Camera Model)
        cloudRGB.points[i].r = get<2>(RGB_Color); // Reference tuple<2>
        cloudRGB.points[i].g = get<1>(RGB_Color); // Reference tuple<1>
        cloudRGB.points[i].b = get<0>(RGB_Color); // Reference tuple<0>

    }
    


   return std::tuple<pcl::PointCloud<pcl::PointXYZRGB>, pcl::PointCloud<pcl::PointXYZ>>(cloudRGB, cloud);
}

pcl::PointCloud<pcl::PointXYZRGB>::Ptr PCL_Conversion(const rs2::points& points, const rs2::video_frame& color){

    // Object Declaration (Point Cloud)
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);

    // Declare Tuple for RGB value Storage (<t0>, <t1>, <t2>)
    std::tuple<uint8_t, uint8_t, uint8_t> RGB_Color;

    //================================
    // PCL Cloud Object Configuration
    //================================
    // Convert data captured from Realsense camera to Point Cloud
    auto sp = points.get_profile().as<rs2::video_stream_profile>();
    
    cloud->width  = static_cast<uint32_t>( sp.width()  );   
    cloud->height = static_cast<uint32_t>( sp.height() );
    cloud->is_dense = false;
    cloud->points.resize( points.size() );

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

pcl::PointCloud<pcl::PointXYZ> RSCameraHandler::convertToPCL(){
    pcl::PointCloud<pcl::PointXYZ> newCloud;
    // Declare pointcloud object, for calculating pointclouds and texture mappings
    rs2::pointcloud pc;


    // Capture a single frame and obtain depth + RGB values from it    
        auto frames = RSCameraHandler::pipe.wait_for_frames();
        auto depth = frames.get_depth_frame();
        auto RGB = frames.get_color_frame();

        // Map Color texture to each point
        pc.map_to(RGB);

        // Generate Point Cloud
        auto points = pc.calculate(depth);

        // Object Declaration (Point Cloud)
    pcl::PointCloud<pcl::PointXYZ> cloud;

    std::tuple<uint8_t, uint8_t, uint8_t> RGB_Color;

    auto sp = points.get_profile().as<rs2::video_stream_profile>();
    
    cloud.width  = static_cast<uint32_t>( sp.width()  );   
    cloud.height = static_cast<uint32_t>( sp.height() );
    cloud.is_dense = false;
    cloud.points.resize( points.size() );

    auto Texture_Coord = points.get_texture_coordinates();
    auto Vertex = points.get_vertices();

    for (int i = 0; i < points.size(); i++)
    {   
        cloud.points[i].x = Vertex[i].x;
        cloud.points[i].y = Vertex[i].y;
        cloud.points[i].z = Vertex[i].z;
    }

    return cloud;
}

pcl::PointCloud<pcl::PointXYZRGB> RSCameraHandler::convertToRGBPCL() {
    pcl::PointCloud<pcl::PointXYZRGB> newCloud;
    // Declare pointcloud object, for calculating pointclouds and texture mappings
    rs2::pointcloud pc;


    // Capture a single frame and obtain depth + RGB values from it    
        auto frames = RSCameraHandler::pipe.wait_for_frames();
        auto depth = frames.get_depth_frame();
        auto RGB = frames.get_color_frame();

        // Map Color texture to each point
        pc.map_to(RGB);

        // Generate Point Cloud
        auto points = pc.calculate(depth);

        // Object Declaration (Point Cloud)
    pcl::PointCloud<pcl::PointXYZRGB> cloud;

    std::tuple<uint8_t, uint8_t, uint8_t> RGB_Color;

    auto sp = points.get_profile().as<rs2::video_stream_profile>();
    
    cloud.width  = static_cast<uint32_t>( sp.width()  );   
    cloud.height = static_cast<uint32_t>( sp.height() );
    cloud.is_dense = false;
    cloud.points.resize( points.size() );

    auto Texture_Coord = points.get_texture_coordinates();
    auto Vertex = points.get_vertices();

    for (int i = 0; i < points.size(); i++)
    {   
        cloud.points[i].x = Vertex[i].x;
        cloud.points[i].y = Vertex[i].y;
        cloud.points[i].z = Vertex[i].z;

        cloud.points[i].r = 255;
        cloud.points[i].g = 255;
        cloud.points[i].b = 255;
    }

    return cloud;
}

void RSCameraHandler::grabImage(){
    
}

void RSCameraHandler::runThread() {
        while(true){
            RSCameraHandler::grabImage();
            // auto thing = convertBothPCL();
            RSCameraHandler::setLatestCloud(convertToRGBPCL());
            RSCameraHandler::setLatestCloud(convertToPCL());
        }
}

void RSCameraHandler::threadRunner() {

}

void RSCameraHandler::connectCamera(){

    std::vector<std::string> serials;

    for (auto&& dev : ctx.query_devices()) {

        serials.push_back(dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER));
        std::cout << dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER) << std::endl;
    }
        
    std::vector<std::string> connectedCams = CameraConnector::getInstance()->getConnectedRSCameras();
    for (std::string serial : serials)
    {   
        bool hasBeenConnected = false;
        for (size_t i = 0; i < connectedCams.size(); i++)
        {
            if (connectedCams.at(i) == serial) {
                hasBeenConnected = true;
                break;
            }
        }
        if (!hasBeenConnected) {
            config.enable_device(serial);
            pipe.start(config);
            pipeRunning = true;
            auto depth_sensor = pipe.get_active_profile().get_device().first<rs2::depth_sensor>();
            
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
            CameraConnector::getInstance()->addConnectedRSCamera(serial);
            return;
        }
    }
    std::cout << "No available device found" << std::endl;
    
}

    pcl::PointCloud<pcl::PointXYZ> RSCameraHandler::getLatestPointCloud() {

        pcl::PointCloud<pcl::PointXYZ> cloudCopy;
        CameraHandler::latestCloud_mtx.lock();
        cloudCopy = CameraHandler::latestCloud;
        CameraHandler::latestCloud_mtx.unlock();
        return cloudCopy;
    }
    
    pcl::PointCloud<pcl::PointXYZRGB> RSCameraHandler::getLatestPointCloudRGB() {
        pcl::PointCloud<pcl::PointXYZRGB> cloudCopy;
        CameraHandler::latestRGBCloud_mtx.lock();
        cloudCopy = CameraHandler::latestRGBCloud;
        CameraHandler::latestRGBCloud_mtx.unlock();
        return cloudCopy;
    }

    bool RSCameraHandler::getPipeRunning() {
        return pipeRunning;
    }