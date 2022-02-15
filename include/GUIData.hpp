#pragma once

#include "Information3D.hpp"
#include <QApplication>
#include <QObject>

using namespace std;

struct vec3 {
    float x;
    float y;
    float z;
};
struct vec2 {
    float x;
    float y;
};

struct Object2D {
    vec2 position;
    vec2 direction;
};

struct VisualObject {
    int id;
    int showTime;
    vec3 position;
    double size;
    float directionHor;
    float directionVer;
    double speed;
    double acceleration;
};

struct StatisticsObject {
    int uptime; // Seconds

};

struct DataFlags {
    bool view2d, visualobject, stats;
};

class GUIData
{
    public:
        static GUIData* getInstance();

        int setObjects(vector<VisualObject> objects);
        int setObjects(Information3D newData);
        
        int setStatistics(StatisticsObject stats);  // Not sure how to implement

        bool configuring = true;

        vector<Object2D> getView2D();

        vector<VisualObject> getTable();
        
        StatisticsObject getStats();

        DataFlags getDataFlags();

        vector<QWidget*> configWindows;

    private:
        GUIData();
        static GUIData* instance;

        vector<Object2D> view2d;
        bool view2d_busy, view2d_newdata;
        
        vector<VisualObject> table;
        bool table_busy, table_newdata;
        
        StatisticsObject stats;
        bool stats_busy, stats_newdata;

};