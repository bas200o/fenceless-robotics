/*Class used for the GUI*/
#pragma once

#include <vector>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QTableView>
#include <QTableWidget>
#include <QGraphicsView>

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

        GUIData(QList<Object2D> view2dObjects, 
                QList<VisualObject> tableObjects, 
                StatisticsObject stats);

    public Q_SLOTS: // Coming from the worker threads
        void addObject_2d(Object2D obj);
        void addObject_table(VisualObject obj);
        
        void updateObject_2d(Object2D obj);
        void updateObject_table(VisualObject obj);
        void updateObject_statistics(StatisticsObject obj);

    Q_SIGNALS: // Going to the UI
        void changed_2d(QList<Object2D> objects);
        void changed_table(QList<VisualObject> objects);
        void changed_statistics(StatisticsObject object);

};

class GUIApplication : public QWidget
{
    private:
        QGraphicsView *pan_view2d;
        QWidget *pan_view3d;
        QWidget *pan_statistics;
        QTableWidget *pan_table;

        QGridLayout *layout;

        QTableWidgetItem *tableObjects[9][10];
        QStringList tableHeaders = { 
            "ID", 
            "Tijd in beeld", 
            "PosX", 
            "PosY", 
            "PosZ", 
            "Formaat", 
            "Snelheid",
            "Richting", 
            "Versnelling" };

    public:
        explicit GUIApplication(QWidget *parent = 0);

        int insertObject(VisualObject obj);
        int updateObject(int id, VisualObject obj);
        void destroyObject(int id);

};
