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

/**
 * Main methode for pcl application
 * @return stopcode
 */
int DataManager::dataMain()
{
    Controller3D cont3;
    // float longest = 0, shortest = 99;
    bool first = true;
    while(true)
    {
        std::clock_t start;
        double duration;
        start = std::clock();

        cont3.CreateNewInformation();
        while(GUIData::getInstance()->configuring){
            cont3.configure();
        }
        cont3.ProccesPointcloud();
        cont3.DetectObjects(0);
        cont3.assignIdentification();
        cont3.CalculateSpeed();
        cont3.calculateDirection();
        cont3.pushUIData();

        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

        first = false;
        std::cout<<"duration of inference with intake and delays: "<< duration << std::endl;
    }
    cout << "ended application" << endl;
    return 1;
}

/**
 * Starts Program in new thread
 * @return stopcode
 */
int DataManager::startThreads(int argc, char **argv) 
{
    arena.enqueue( [&] 
    {
        dataMain();
    });
    return 1;
}

/**
 * Starts the gui
 * @param Arguments from main
 * @return stopcode
 */
int DataManager::maingui(int argc, char **argv)
{
    QApplication app(argc, argv);
    GUIData *guiData = guiData->getInstance();
    GUIApplication gui;

    

    arena.enqueue( [&] // UI update worker
    {
        this_thread::sleep_for(std::chrono::seconds(5));

        while(true)
        {
            DataFlags df = GUIData::getInstance()->getDataFlags();

            if(df.view2d)
                gui.update2d(GUIData::getInstance()->getView2D());

            if(df.visualobject)
                gui.updateTable(GUIData::getInstance()->getTable());

            if(df.stats)
                gui.updateStatistics(GUIData::getInstance()->getStats());

            this_thread::sleep_for(std::chrono::milliseconds(300));    
        }
    });

#ifndef __DEBUG_UI
    // arena.enqueue( [&] { // Filling UI with values

    //     this_thread::sleep_for(std::chrono::seconds(5));        
    //     GUIData::getInstance()->setObjects(vector<VisualObject> {
    //         { , 1, {10, 20, 30}, 0.0f, {100, 200, 300}, 123, 567 },
    //         { , 2, {12, 22, 32}, 0.0f, {102, 202, 302}, 123, 567 }, 
    //         { , 3, {13, 23, 33}, 0.3f, {103, 203, 303}, 123, 456 }
    //     });
    // });
#endif
    

    gui.show();
    return app.exec();
}
