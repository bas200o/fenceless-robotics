#pragma once

#include "Information3D.hpp"
#include <QApplication>
#include <QObject>

using namespace std;

struct vec3 {
    int x;
    int y;
    int z;
};
struct vec2 {
    int x;
    int y;
};

struct Object2D {
    vec2 position;
    vec2 direction;
};

struct VisualObject {
    int showTime;
    vec3 position;
    double size;
    vec3 direction;
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