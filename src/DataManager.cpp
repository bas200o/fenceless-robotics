#include "../include/RobotController.hpp"
#include "../include/GUIApplication.hpp"
#include "../include/Controller3D.hpp"
#include "../include/Controller2D.hpp"
#include "../include/CameraConnector.hpp"

// #include <tbb/tbb_thread.h>
// #include <tbb/tbb.h>
// #include <tbb/spin_mutex.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "oneapi/tbb/parallel_for.h"
#include "oneapi/tbb/task_arena.h"
// #include <tbb/parallel_for.h>

int buildUI(int argc, char **argv)
{
    QApplication app(argc, argv);
    GUIApplication gui;
    gui.show();
    return app.exec();
}


int main(int argc, char **argv)
{
    CameraConnector *camCon = camCon->getInstance();
    camCon->connectCameras(2, 1);

    tbb::task_arena arena;

    arena.enqueue( [] {

        CameraConnector *camCon = CameraConnector::getInstance();
        camCon->connectCameras(2, 1);

        Controller3D cont3;
        Controller2D cont2;

        cout << "Hello vision!" << endl;

        // while(true)
            //Do 3D vision

    });
    

    QApplication app(argc, argv);
    GUIApplication gui;
    gui.show();

    return app.exec();
}
