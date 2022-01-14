#include "../include/RobotController.hpp"
#include "../include/GUIApplication.hpp"
#include "../include/Controller3D.hpp"
#include "../include/Controller2D.hpp"
#include "../include/CameraConnector.hpp"

// #include <tbb/tbb_thread.h>
// #include <tbb/tbb.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "oneapi/tbb/parallel_for.h"
#include "oneapi/tbb/task_arena.h"


int main(int argc, char **argv)
{
    CameraConnector *camCon = camCon->getInstance();

    QApplication app(argc, argv);
    GUIData guiData;
    GUIApplication gui;


    tbb::task_arena arena;

    arena.enqueue( [&] {
        
        camCon->connectCameras(2, 1);

        Controller3D cont3;
        Controller2D cont2;

        cout << "Hello vision!" << endl;

        // while(true)
            //Do 3D vision

    });

    arena.enqueue( [&] 
    {
        // QObject::connect(&guiData, &GUIData::changed_table, &gui, &GUIApplication::updateTable);

        // guiData.updateTable(QList<VisualObject> {});
    });
    


    // GUIData::connect(&guiData, &GUIData::changed_table, 
    //                     &gui, &GUIApplication::updateTable);
    // QObject::connect(&guiData, &GUIData::changed_statistics,
    //                     &gui, &GUIApplication::updateStatistics);
    // QObject::connect(&guiData, &GUIData::changed_2d,
    //                     &gui, &GUIApplication::update2d);

    gui.show();

    return app.exec();
}
