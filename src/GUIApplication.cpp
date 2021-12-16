#include "../include/GUIApplication.hpp"

GUIApplication::GUIApplication(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1240, 830);

// Panel 2D View
    pan_view2d = new QPushButton(" 2D View ");
    pan_view2d->setFixedSize(400, 400);
    
// Panel 3D View
    pan_view3d = new QPushButton(" 3D View ");
    pan_view3d->setFixedSize(400, 400);

    // Panel Statistics
    pan_statistics = new QPushButton();
    pan_statistics->setFixedSize(400, 400);

// Panel Table
    pan_table = new QTableWidget(this);
    pan_table->setFixedSize(1220, 400);

    pan_table->setRowCount(sizeof(tableObjects[0]));
    pan_table->setColumnCount(9);
    pan_table->setHorizontalHeaderLabels(tableHeaders);

    // Filling 5 rows with zeroes as a starter
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 5; j++)
            tableObjects[i][j] = new QTableWidgetItem(tr("%1").arg(0));
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 5; j++)
            pan_table->setItem(j, i, tableObjects[i][j]);

// Combining layout
    layout = new QGridLayout(this);
    layout->addWidget(pan_view2d, 0, 0);
    layout->addWidget(pan_view3d, 0, 1);
    layout->addWidget(pan_statistics, 0, 2);
    layout->addWidget(pan_table, 1, 0, 1, 3);

}
