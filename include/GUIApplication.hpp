/*Class used for the GUI*/
#pragma once

#include "Information3D.hpp"
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QTableView>
#include <QTableWidget>
#include <QGraphicsView>
#include "../include/GUIData.hpp"

class GUIApplication : public QWidget
{
    
    private:
        QGraphicsView *pan_view2d;
        QWidget *pan_view3d;
        QWidget *pan_statistics;
        QTableWidget *pan_table;

        QGridLayout *layout;

        QStringList tableHeaders = { 
            "ID", 
            "Tijd in beeld", 
            "Positie", 
            "Diameter", 
            "Richting", 
            "Snelheid",
            "Versnelling" };

    public:
        explicit GUIApplication(QWidget *parent = 0);
        virtual ~GUIApplication() {};

        int insertObject(VisualObject obj);
        int updateObject(int id, VisualObject obj);
        void destroyObject(int id);

    public Q_SLOTS:
        void update2d(QList<Object2D> objects);
        void updateTable(QList<VisualObject> objects);
        void updateStatistics(StatisticsObject object);
        
};
