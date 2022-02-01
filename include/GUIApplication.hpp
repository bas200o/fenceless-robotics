/*Class used for the GUI*/
#pragma once

#include "Information3D.hpp"
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QTableView>
#include <QTableWidget>
#include <QGraphicsView>
#include <QSlider>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QCheckBox>
#include "../include/GUIData.hpp"

class GUIApplication : public QWidget
{
    
    private:
        QGraphicsView *pan_view2d;
        QWidget *pan_view3d;
        QWidget *pan_statistics;
        QTableWidget *pan_table;

        vector<QSlider>moveXSliders;
        vector<QSlider>moveYSliders;
        vector<QSlider>moveZSliders;

        vector<QSlider>rotateXSliders;
        vector<QSlider>rotateYSliders;
        vector<QSlider>rotateZSliders;
        vector<QSlider>rotate2XSliders;
        vector<QSlider>rotate2YSliders;
        vector<QSlider>rotate2ZSliders;

        vector<QSlider>filterXSliders;
        vector<QSlider>filterYSliders;
        vector<QSlider>filterZSliders;
        vector<QSlider>filter2XSliders;
        vector<QSlider>filter2YSliders;
        vector<QSlider>filter2ZSliders;

        vector <QCheckBox>checkBoxes;

        void addPclWindow(int id);
        QSlider* getDefaultSlider(int val= 0, int min = -4000, int max = 4000);

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
        
        static void ValueChange(int v);

        static void rotationChangeX(int X);
        static void rotationChangeY(int Y);
        static void rotationChangeZ(int Z);
        static void positionChangeX(int X);
        static void positionChangeY(int Y);
        static void positionChangeZ(int Z);

        static void rotationChangeX1(int X);
        static void rotationChangeY1(int Y);
        static void rotationChangeZ1(int Z);
        static void positionChangeX1(int X);
        static void positionChangeY1(int Y);
        static void positionChangeZ1(int Z);

        static void filterChangex(int v);
        static void filterChangex1(int v);
        static void filterChangey(int v);
        static void filterChangey1(int v);
        static void filterChangez(int v);
        static void filterChangez1(int v);
        static void setConfiguring();

        void update2d(vector<Object2D> objects);
        void updateTable(vector<VisualObject> objects);
        void updateStatistics(StatisticsObject object);
        
};
