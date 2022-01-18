#include "../include/RobotController.hpp"
#include "../include/GUIApplication.hpp"
#include "../include/Controller3D.hpp"
#include "../include/Controller2D.hpp"
#include "../include/CameraConnector.hpp"

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
    GUIData *guiData = guiData->getInstance();
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
    


    gui.show();

    return app.exec();
}
