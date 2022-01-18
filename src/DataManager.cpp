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
    QApplication app(argc, argv);
    GUIData *guiData = guiData->getInstance();
    GUIApplication gui;

    tbb::task_arena arena;

    arena.enqueue( [&] 
    {
        this_thread::sleep_for(std::chrono::seconds(5));

        while(true)
        {
            DataFlags df = GUIData::getInstance()->getDataFlags();
            cout << "Dataflags: " << df.view2d << df.visualobject << df.stats << endl;

            if(df.view2d)
                gui.update2d(GUIData::getInstance()->getView2D());

            if(df.visualobject)
                gui.updateTable(GUIData::getInstance()->getTable());

            if(df.stats)
                gui.updateStatistics(GUIData::getInstance()->getStats());

            this_thread::sleep_for(std::chrono::seconds(2));    
        }
    });

#ifndef __DEBUG_UI
    arena.enqueue( [&] {

        cout << "Filling with random objects in 5 seconds" << endl;
        this_thread::sleep_for(std::chrono::seconds(5));        
        GUIData::getInstance()->setObjects(vector<VisualObject> {
            { 1, {10, 20, 30}, 0.0f, {100, 200, 300}, 123, 567 },
            { 2, {12, 22, 32}, 0.0f, {102, 202, 302}, 123, 567 }, 
            { 3, {13, 23, 33}, 0.3f, {103, 203, 303}, 123, 456 }
        });
    });
#endif
    

    gui.show();
    return app.exec();
}
