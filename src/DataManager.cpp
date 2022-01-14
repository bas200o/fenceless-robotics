#include "../include/RobotController.hpp"
#include "../include/GUIApplication.hpp"
#include "../include/Controller3D.hpp"
#include "../include/Controller2D.hpp"
#include "../include/CameraConnector.hpp"

int oldmain()
{
    CameraConnector *camCon = camCon->getInstance();
    camCon->connectCameras(2, 1);
    GUIApplication gui;
    Controller3D cont3;
    cont3.CreateNewInformation();
    cont3.DetectObjects(0);

    //Controller2D cont2;
    //while(true)

    //Do 3DVision
    cout << "ended \n";
    return 1;
}