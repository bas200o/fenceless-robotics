#include "../include/GUIApplication.hpp"

GUIApplication::GUIApplication(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1240, 830);
    setWindowTitle("Fenceless Robotics");

// Panel 2D View
    QGraphicsScene scene;
    QGraphicsRectItem *rect = scene.addRect(QRectF(0, 0, 100, 100));

    QGraphicsItem *item = scene.itemAt(50, 50, QTransform());

    pan_view2d = new QGraphicsView(&scene);
    pan_view2d->setFixedSize(400, 400);


    
// Panel 3D View
    pan_view3d = new QPushButton(" 3D View ");
    pan_view3d->setFixedSize(400, 400);

    // Panel Statistics
    pan_statistics = new QPushButton(" Stats ");
    pan_statistics->setFixedSize(400, 400);
    

// Panel Table
    pan_table = new QTableWidget(this);
    pan_table->setFixedSize(1220, 400);

    pan_table->setRowCount(1);
    pan_table->setColumnCount(tableHeaders.count());
    pan_table->setHorizontalHeaderLabels(tableHeaders);

    // Filling 1 row with zeroes as a starter
    for (int i = 0; i < 7; i++)
    {
        pan_table->setItem(0, i, new QTableWidgetItem("0"));
    }

// Combining layout
    layout = new QGridLayout(this);
    layout->addWidget(pan_view2d, 0, 0);
    layout->addWidget(pan_view3d, 0, 1);
    layout->addWidget(pan_statistics, 0, 2);
    layout->addWidget(pan_table, 1, 0, 1, 3);

}

void GUIApplication::updateTable(QList<VisualObject> objects)
{
    pan_table->setRowCount(objects.count());
    int row = 0;
    for(VisualObject obj : objects)
    {
        QString pos = QString("[%1,%2,%3]").arg(obj.position.x, obj.position.y, obj.position.z);
        QString dir = QString("[%1,%2,%3]").arg(obj.direction.x, obj.direction.y, obj.direction.z);

        pan_table->setItem(row, 0, new QTableWidgetItem("-"));              // ID
        pan_table->setItem(row, 1, new QTableWidgetItem("-"));              // Tijd in beeld
        pan_table->setItem(row, 2, new QTableWidgetItem(pos));              // Positie
        pan_table->setItem(row, 3, new QTableWidgetItem(obj.size));         // Diameter
        pan_table->setItem(row, 4, new QTableWidgetItem(dir));              // Richting
        pan_table->setItem(row, 5, new QTableWidgetItem(obj.speed));        // Snelheid
        pan_table->setItem(row, 6, new QTableWidgetItem(obj.acceleration)); // Versnelling

        row++;
    }   
    pan_table->repaint();
}

void GUIApplication::update2d(QList<Object2D> objects){}
void GUIApplication:: updateStatistics(StatisticsObject obj){}
