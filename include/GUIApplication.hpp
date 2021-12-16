/*Class used for the GUI*/
#pragma once

#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QTableView>
#include <QTableWidget>

struct vec3 {
    int x;
    int y;
    int z;
};

struct VisualObject {
    int showTime;
    vec3 position;
    double size;
    vec3 direction;
    double speed;
    double acceleration;
};

class GUIApplication : public QWidget
{
    private:
        QWidget *pan_view2d;
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


