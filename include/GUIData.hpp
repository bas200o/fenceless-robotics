#pragma once

#include "Information3D.hpp"
#include <QApplication>
#include <QObject>

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

class GUIData : public QObject
{
    Q_OBJECT

    public:

        QList<Object2D> view2d;
        QList<VisualObject> table;
        StatisticsObject stats;

        GUIData();
   /*     GUIData(QList<Object2D> view2dObjects, 
                QList<VisualObject> tableObjects, 
                StatisticsObject stats);*/
        virtual ~GUIData() {};

    public Q_SLOTS: // Coming from the worker threads
        void addObject_2d(Object2D obj);
        void addObject_table(VisualObject obj);
        
        void updateObject_2d(Object2D obj);
        void updateObject_table(VisualObject obj);
        void updateObject_statistics(StatisticsObject obj);

        void updateTable(QList<VisualObject> newTable);
        void updateTable(Information3D newData);

    Q_SIGNALS: // Going to the UI
        void changed_2d(QList<Object2D> objects);
        void changed_table(QList<VisualObject> objects);
        void changed_statistics(StatisticsObject object);

};