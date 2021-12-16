#include "../include/RobotController.hpp"
#include "../include/GUIApplication.hpp"
#include "../include/Controller3D.hpp"
#include "../include/Controller2D.hpp"
#include "../include/CameraConnector.hpp"

int main(int argc, char **argv)
{
    CameraConnector *camCon = camCon->getInstance();
    camCon->connectCameras(2, 1);

    QApplication app(argc, argv);
    GUIApplication gui;
    gui.show();
    app.exec();

    Controller3D cont3;
    Controller2D cont2;
    //while(true)
    std::cout << "Hello vision!" << endl;
    //Do 3DVision
}