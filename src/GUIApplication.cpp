#include "../include/GUIApplication.hpp"
#include "../include/SettingSingleton.hpp"
#include <iostream>

void GUIApplication::rotationChangeX(int x)
{
    SettingSingleton *ds = ds->getInstance();
    struct rotationSettings rs = ds->getRotate();
    rs.x = (float)(x / 1000.0);
    ds->setRotate(rs);
}

void GUIApplication::rotationChangeY(int y)
{
    SettingSingleton *ds = ds->getInstance();
    struct rotationSettings rs = ds->getRotate();
    rs.y = (float)(y / 1000.0);
    ds->setRotate(rs);
}

void GUIApplication::rotationChangeZ(int z)
{
    SettingSingleton *ds = ds->getInstance();
    struct rotationSettings rs = ds->getRotate();
    rs.z = (float)(z / 1000.0);
    ds->setRotate(rs);
}

void GUIApplication::positionChangeX(int x)
{
    SettingSingleton *ds = ds->getInstance();
    struct moveSettings rs = ds->getMove();
    rs.x = (float)(x / 1000.0);
    ds->setMove(rs);
}

void GUIApplication::positionChangeY(int y)
{
    SettingSingleton *ds = ds->getInstance();
    struct moveSettings rs = ds->getMove();
    rs.y = (float)(y / 1000.0);
    ds->setMove(rs);
}

void GUIApplication::positionChangeZ(int z)
{
    SettingSingleton *ds = ds->getInstance();
    struct moveSettings rs = ds->getMove();
    rs.z = (float)(z / 1000.0);
    ds->setMove(rs);
}

void GUIApplication::filterChangex(int v)
{
    SettingSingleton *ds = ds->getInstance();
    struct filterSettings fs = ds->getFilter();
    fs.x = (float)(v / 1000.0);
    ds->setFilter(fs);
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
    sliderMvX->setMinimum(-4000);
    sliderMvX->setMaximum(4000);
    connect(sliderMvX, &QSlider::valueChanged, this, GUIApplication::positionChangeX);
    auto sliderMvY = new QSlider(Qt::Horizontal);
    sliderMvY->setMinimum(-4000);
    sliderMvY->setMaximum(4000);
    connect(sliderMvY, &QSlider::valueChanged, this, GUIApplication::positionChangeY);
    auto sliderMvZ = new QSlider(Qt::Horizontal);
    sliderMvZ->setMinimum(-4000);
    sliderMvZ->setMaximum(4000);
    connect(sliderMvZ, &QSlider::valueChanged, this, GUIApplication::positionChangeZ);
    auto sliderRtX = new QSlider(Qt::Horizontal);
    sliderRtX->setMinimum(-4000);
    sliderRtX->setMaximum(4000);
    connect(sliderRtX, &QSlider::valueChanged, this, GUIApplication::rotationChangeX);
    auto sliderRtY = new QSlider(Qt::Horizontal);
    sliderRtY->setMinimum(-4000);
    sliderRtY->setMaximum(4000);
    connect(sliderRtY, &QSlider::valueChanged, this, GUIApplication::rotationChangeY);
    auto sliderRtZ = new QSlider(Qt::Horizontal);
    sliderRtZ->setMinimum(-4000);
    sliderRtZ->setMaximum(4000);
    connect(sliderRtZ, &QSlider::valueChanged, this, GUIApplication::rotationChangeZ);

    auto sliderFX = new QSlider(Qt::Horizontal);
    sliderFX->setMinimum(-4000);
    sliderFX->setMaximum(4000);
    connect(sliderFX, &QSlider::valueChanged, this, GUIApplication::filterChangex);


    auto mx = new QLabel("move x");
    auto my = new QLabel("move y");
    auto mz = new QLabel("move z");
    auto rx = new QLabel("rotate x");
    auto ry = new QLabel("rotate y");
    auto rz = new QLabel("rotate z");

    // Combining layout
    layout = new QGridLayout(this);
    layout->addWidget(pan_view2d, 0, 0);
    layout->addWidget(pan_view3d, 0, 1);
    layout->addWidget(pan_statistics, 0, 2);
    layout->addWidget(pan_table, 1, 0, 1, 3);

    layout->addWidget(sliderMvX, 2, 1, 1, 2);
    layout->addWidget(mx, 2, 0, 1, 1);
    layout->addWidget(sliderMvY, 3, 1, 1, 2);
    layout->addWidget(my, 3, 0, 1, 1);
    layout->addWidget(sliderMvZ, 4, 1, 1, 2);
    layout->addWidget(mz, 4, 0, 1, 1);
    layout->addWidget(sliderRtX, 5, 1, 1, 2);
    layout->addWidget(rx, 5, 0, 1, 1);
    layout->addWidget(sliderRtY, 6, 1, 1, 2);
    layout->addWidget(ry, 6, 0, 1, 1);
    layout->addWidget(sliderRtZ, 7, 1, 1, 2);
    layout->addWidget(rz, 7, 0, 1, 1);

    layout->addWidget(sliderFX, 8, 1, 1, 2);
}