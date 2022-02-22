/*Controls the main application
*/

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

#pragma once

class DataManager
{
    private: 
        tbb::task_arena arena;
        
    public:
        int dataMain();

        int buildUI(int argc, char **argv);

        int maingui(int argc, char **argv);

        int startThreads(int argc, char **argv);

};