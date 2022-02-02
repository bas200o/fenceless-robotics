/*Class used for the GUI*/
#pragma once

#include "Information3D.hpp"
#include "CameraConnector.hpp"
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

        vector<QSlider*>moveXSliders;
        vector<QSlider*>moveYSliders;
        vector<QSlider*>moveZSliders;

        vector<QSlider*>rotateXSliders;
        vector<QSlider*>rotateYSliders;
        vector<QSlider*>rotateZSliders;
        vector<QSlider*>rotate1XSliders;
        vector<QSlider*>rotate1YSliders;
        vector<QSlider*>rotate1ZSliders;

        vector<QSlider*>filterXSliders;
        vector<QSlider*>filterYSliders;
        vector<QSlider*>filterZSliders;
        vector<QSlider*>filter1XSliders;
        vector<QSlider*>filter1YSliders;
        vector<QSlider*>filter1ZSliders;

        vector <QCheckBox*>checkBoxes;

        void rotationChangeX(int id);
        void rotationChangeY(int id);
        void rotationChangeZ(int id);
        void positionChangeX(int id);
        void positionChangeY(int id);
        void positionChangeZ(int id);

        void rotationChangeX1(int id);
        void rotationChangeY1(int id);
        void rotationChangeZ1(int id);
        void positionChangeX1(int id);
        void positionChangeY1(int id);
        void positionChangeZ1(int id);

        void filterChangex(int id);
        void filterChangex1(int id);
        void filterChangey(int id);
        void filterChangey1(int id);
        void filterChangez(int id);
        void filterChangez1(int id);

        void checkBoxClicked(int id);

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
        static void setConfiguring();

        void update2d(vector<Object2D> objects);
        void updateTable(vector<VisualObject> objects);
        void updateStatistics(StatisticsObject object);
        
};
