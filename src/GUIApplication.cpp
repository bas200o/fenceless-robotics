#include "../include/GUIApplication.hpp"
#include "../include/SettingSingleton.hpp"
#include <iostream>

void GUIApplication::rotationChangeX(int x) {
    SettingSingleton *ds = ds->getInstance();
    struct rotationSettings rs = ds->getRotate();
    rs.x = (float)(x/1000.0);
    ds->setRotate(rs);

    std::cout << rs.x << "X " << rs.y << "Y " << rs.z << "Z " << std::endl;
}

void GUIApplication::rotationChangeY(int y) {
    SettingSingleton *ds = ds->getInstance();
    struct rotationSettings rs = ds->getRotate();
    rs.y = (float)(y/1000.0);
    ds->setRotate(rs);

    std::cout << rs.x << "X " << rs.y << "Y " << rs.z << "Z " << std::endl;
}

void GUIApplication::rotationChangeZ(int z) {
    SettingSingleton *ds = ds->getInstance();
    struct rotationSettings rs = ds->getRotate();
    rs.z = (float)(z/1000.0);
    ds->setRotate(rs);

    std::cout << rs.x << "X " << rs.y << "Y " << rs.z << "Z " << std::endl;
}

void GUIApplication::positionChangeX(int x) {
    SettingSingleton *ds = ds->getInstance();
    struct moveSettings rs = ds->getMove();
    rs.x = (float)(x/1000.0);
    ds->setMove(rs);
}

void GUIApplication::positionChangeY(int y) {
    SettingSingleton *ds = ds->getInstance();
    struct moveSettings rs = ds->getMove();
    rs.y = (float)(y/1000.0);
    ds->setMove(rs);
}

void GUIApplication::positionChangeZ(int z) {
    SettingSingleton *ds = ds->getInstance();
    struct moveSettings rs = ds->getMove();
    rs.z = (float)(z/1000.0);
    ds->setMove(rs);
}


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

    pan_table->setRowCount(sizeof(tableObjects) / sizeof(tableObjects[0]));
    pan_table->setColumnCount(9);
    pan_table->setHorizontalHeaderLabels(tableHeaders);

    // Filling 5 rows with zeroes as a starter
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 5; j++)
            tableObjects[i][j] = new QTableWidgetItem(tr("%1").arg(0));
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 5; j++)
            pan_table->setItem(j, i, tableObjects[i][j]);


    auto name = new QLabel("Hey Link Listen");
    auto sliderMvX = new QSlider(Qt::Horizontal);
    sliderMvX->setMinimum(-1000);
    sliderMvX->setMaximum(1000);
    connect(sliderMvX, &QSlider::valueChanged, this, GUIApplication::positionChangeX);
    auto sliderMvY = new QSlider(Qt::Horizontal);
    sliderMvY->setMinimum(-1000);
    sliderMvY->setMaximum(1000);
    connect(sliderMvY, &QSlider::valueChanged, this, GUIApplication::positionChangeY);
        auto sliderMvZ = new QSlider(Qt::Horizontal);
    sliderMvZ->setMinimum(-1000);
    sliderMvZ->setMaximum(1000);
    connect(sliderMvZ, &QSlider::valueChanged, this, GUIApplication::positionChangeZ);
        auto sliderRtX = new QSlider(Qt::Horizontal);
    sliderRtX->setMinimum(-1000);
    sliderRtX->setMaximum(1000);
    connect(sliderRtX, &QSlider::valueChanged, this, GUIApplication::rotationChangeX);
        auto sliderRtY = new QSlider(Qt::Horizontal);
    sliderRtY->setMinimum(-1000);
    sliderRtY->setMaximum(1000);
    connect(sliderRtY, &QSlider::valueChanged, this, GUIApplication::rotationChangeY);
        auto sliderRtZ = new QSlider(Qt::Horizontal);
    sliderRtZ->setMinimum(-1000);
    sliderRtZ->setMaximum(1000);
    connect(sliderRtZ, &QSlider::valueChanged, this, GUIApplication::rotationChangeZ);


    // Combining layout
    layout = new QGridLayout(this);
    layout->addWidget(pan_view2d, 0, 0);
    layout->addWidget(pan_view3d, 0, 1);
    layout->addWidget(pan_statistics, 0, 2);
    layout->addWidget(pan_table, 1, 0, 1, 3);



    layout->addWidget(sliderMvX, 2, 0, 1, 3);
    layout->addWidget(sliderMvY, 3, 0, 1, 3);
    layout->addWidget(sliderMvZ, 4, 0, 1, 3);
    layout->addWidget(sliderRtX, 5, 0, 1, 3);
    layout->addWidget(sliderRtY, 6, 0, 1, 3);
    layout->addWidget(sliderRtZ, 7, 0, 1, 3);

    // layout->addWidget(name,3, 2);




}