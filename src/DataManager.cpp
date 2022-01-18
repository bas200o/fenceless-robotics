#include "../include/RobotController.hpp"
#include "../include/GUIApplication.hpp"
#include "../include/Controller3D.hpp"
#include "../include/Controller2D.hpp"
#include "../include/CameraConnector.hpp"
#include "../include/DataManager.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "tbb/parallel_for.h"
#include "tbb/task_arena.h"

int DataManager::dataMain()
{
    
    CameraConnector *camCon = camCon->getInstance();
    camCon->connectCameras(0, 1);
    camCon->connectCameras(1, 1);
    //GUIApplication gui;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Controller3D cont3;
    while(true){
    cont3.CreateNewInformation();
    //cont3.rotate
    //cont3.move
    //cont3.filter
    cont3.CombinePointClouds(0);
    cont3.DetectObjects(0);
    cont3.CalculateSpeed();
    }
    //Controller2D cont2;
    //while(true)

    //Do 3DVision
    cout << "ended \n";
    return 1;
}



int DataManager::maingui(int argc, char **argv)
{
    CameraConnector *camCon = camCon->getInstance();
    // camCon->connectCameras(2, 1);

    QApplication app(argc, argv);
    GUIData *guiData = guiData->getInstance();
    GUIApplication gui;


    tbb::task_arena arena;

    arena.enqueue( [&] {
        

        Controller3D cont3;
        Controller2D cont2;
    });

    arena.enqueue( [&] 
    {
        // QObject::connect(&guiData, &GUIData::changed_table, &gui, &GUIApplication::updateTable);

        // guiData.updateTable(QList<VisualObject> {});
    });
    


    gui.show();

    return app.exec();
}
