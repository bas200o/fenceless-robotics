#include "../include/RobotController.hpp"
#include "../include/GUIApplication.hpp"
#include "../include/Controller3D.hpp"
#include "../include/Controller2D.hpp"
#include "../include/CameraConnector.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tbb/parallel_for.h>
#include <tbb/task_arena.h>

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

int buildUI(int argc, char **argv)
{
    QApplication app(argc, argv);
    GUIApplication gui;
    gui.show();
    return app.exec();
}


int maingui(int argc, char **argv)
{
    CameraConnector *camCon = camCon->getInstance();
    // camCon->connectCameras(2, 1);

    tbb::task_arena arena;

    arena.enqueue( [] {
        Controller3D cont3;
        Controller2D cont2;
    });
    

    QApplication app(argc, argv);
    GUIApplication gui;
    gui.show();

    return app.exec();
}
