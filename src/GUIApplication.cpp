#include "../include/GUIApplication.hpp"
#include "../include/SettingSingleton.hpp"
#include <iostream>

GUIApplication::GUIApplication(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1240, 950);
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
    pan_table->setFixedSize(1220, 300);

    pan_table->setRowCount(1);
    pan_table->setColumnCount(tableHeaders.count());
    pan_table->setColumnWidth(2, 200);
    pan_table->setColumnWidth(4, 200);
    pan_table->setHorizontalHeaderLabels(tableHeaders);

    // Filling 1 row with zeroes as a starter
    for (int i = 0; i < 7; i++)
    {
        pan_table->setItem(0, i, new QTableWidgetItem("0"));
    }

    #pragma region PCL Sliders
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

    // Yannick
    auto sliderMvX1 = new QSlider(Qt::Horizontal);
    sliderMvX1->setMinimum(-4000);
    sliderMvX1->setMaximum(4000);
    connect(sliderMvX1, &QSlider::valueChanged, this, GUIApplication::positionChangeX);
    auto sliderMvY1 = new QSlider(Qt::Horizontal);
    sliderMvY1->setMinimum(-4000);
    sliderMvY1->setMaximum(4000);
    connect(sliderMvY1, &QSlider::valueChanged, this, GUIApplication::positionChangeY);
    auto sliderMvZ1 = new QSlider(Qt::Horizontal);
    sliderMvZ1->setMinimum(-4000);
    sliderMvZ1->setMaximum(4000);
    connect(sliderMvZ1, &QSlider::valueChanged, this, GUIApplication::positionChangeZ);
    auto sliderRtX1 = new QSlider(Qt::Horizontal);
    sliderRtX1->setMinimum(-4000);
    sliderRtX1->setMaximum(4000);
    connect(sliderRtX1, &QSlider::valueChanged, this, GUIApplication::rotationChangeX);
    auto sliderRtY1 = new QSlider(Qt::Horizontal);
    sliderRtY1->setMinimum(-4000);
    sliderRtY1->setMaximum(4000);
    connect(sliderRtY1, &QSlider::valueChanged, this, GUIApplication::rotationChangeY);
    auto sliderRtZ1 = new QSlider(Qt::Horizontal);
    sliderRtZ1->setMinimum(-4000);
    sliderRtZ1->setMaximum(4000);
    connect(sliderRtZ1, &QSlider::valueChanged, this, GUIApplication::rotationChangeZ);

    auto sliderFX = new QSlider(Qt::Horizontal);
    sliderFX->setMinimum(-4000);
    sliderFX->setMaximum(4000);
    connect(sliderFX, &QSlider::valueChanged, this, GUIApplication::filterChangex);
    auto sliderFX1 = new QSlider(Qt::Horizontal);
    sliderFX1->setMinimum(-4000);
    sliderFX1->setMaximum(4000);
    connect(sliderFX1, &QSlider::valueChanged, this, GUIApplication::filterChangex1);
    auto sliderFY = new QSlider(Qt::Horizontal);
    sliderFY->setMinimum(-4000);
    sliderFY->setMaximum(4000);
    connect(sliderFY, &QSlider::valueChanged, this, GUIApplication::filterChangey);
    auto sliderFY1 = new QSlider(Qt::Horizontal);
    sliderFY1->setMinimum(-4000);
    sliderFY1->setMaximum(4000);
    connect(sliderFY1, &QSlider::valueChanged, this, GUIApplication::filterChangey1);
    auto sliderFZ = new QSlider(Qt::Horizontal);
    sliderFZ->setMinimum(-4000);
    sliderFZ->setMaximum(4000);
    connect(sliderFZ, &QSlider::valueChanged, this, GUIApplication::filterChangez);
    auto sliderFZ1 = new QSlider(Qt::Horizontal);
    sliderFZ1->setMinimum(-4000);
    sliderFZ1->setMaximum(4000);
    connect(sliderFZ1, &QSlider::valueChanged, this, GUIApplication::filterChangez1);
    auto pancake = new QPushButton("Stop configuring");
    connect(pancake, &QPushButton::released, this, GUIApplication::setConfiguring);

    auto mx = new QLabel("move x");
    auto my = new QLabel("move y");
    auto mz = new QLabel("move z");
    auto rx = new QLabel("rotate x");
    auto ry = new QLabel("rotate y");
    auto rz = new QLabel("rotate z");
    auto fx = new QLabel("filter x");
    auto fy = new QLabel("filter y");
    auto fz = new QLabel("filter z");

    #pragma endregion PCL Sliders

    // Combining layout
    layout = new QGridLayout(this);
    layout->addWidget(pan_view2d, 0, 0);
    layout->addWidget(pancake, 0, 1);
    layout->addWidget(pan_statistics, 0, 2);
    layout->addWidget(pan_table, 1, 0, 1, 3);

    layout->addWidget(sliderMvX, 2, 1, 1, 1);
    layout->addWidget(mx, 2, 0, 1, 1);
    layout->addWidget(sliderMvY, 3, 1, 1, 1);
    layout->addWidget(my, 3, 0, 1, 1);
    layout->addWidget(sliderMvZ, 4, 1, 1, 1);
    layout->addWidget(mz, 4, 0, 1, 1);
    layout->addWidget(sliderRtX, 5, 1, 1, 1);
    layout->addWidget(rx, 5, 0, 1, 1);
    layout->addWidget(sliderRtY, 6, 1, 1, 1);
    layout->addWidget(ry, 6, 0, 1, 1);
    layout->addWidget(sliderRtZ, 7, 1, 1, 1);
    layout->addWidget(rz, 7, 0, 1, 1);

    layout->addWidget(sliderMvX1, 2, 2, 1, 1);
    layout->addWidget(sliderMvY1, 3, 2, 1, 1);
    layout->addWidget(sliderMvZ1, 4, 2, 1, 1);
    layout->addWidget(sliderRtX1, 5, 2, 1, 1);
    layout->addWidget(sliderRtY1, 6, 2, 1, 1);
    layout->addWidget(sliderRtZ1, 7, 2, 1, 1);

    layout->addWidget(sliderFX, 8, 1, 1, 1);
    layout->addWidget(sliderFX1, 8, 2, 1, 1);
    layout->addWidget(fx, 8, 0, 1, 1);
    layout->addWidget(sliderFY, 9, 1, 1, 1);
    layout->addWidget(sliderFY1, 9, 2, 1, 1);
    layout->addWidget(fy, 9, 0, 1, 1);
    layout->addWidget(sliderFZ, 10, 1, 1, 1);
    layout->addWidget(sliderFZ1, 10, 2, 1, 1);
    layout->addWidget(fz, 10, 0, 1, 1);

}

void GUIApplication::updateTable(vector<VisualObject> objects)
{
    pan_table->setRowCount(objects.size());
    int row = 0;

    // cout << "New ontents of table:\n";

    for(VisualObject obj : objects)
    {
        QString pos = QString("[%1, %2, %3]")
            .arg(obj.position.x)
            .arg(obj.position.y)
            .arg(obj.position.z);
        QString dir = QString("[%1, %2, %3]")
            .arg(obj.direction.x)
            .arg(obj.direction.y)
            .arg(obj.direction.z);

        // cout // brrrr
        //     << row << " | "
        //     << pos.toStdString() << " | "
        //     << obj.size << " | "
        //     << dir.toStdString() << " | "
        //     << obj.speed << " | "
        //     << obj.acceleration 
        // << endl;

        // pan_table->setItem(row, 0, new QTableWidgetItem("-"));                                  // ID -> Removed for now
        pan_table->setItem(row, 1, new QTableWidgetItem(QString("%1").arg(obj.showTime)));      // Tijd in beeld
        pan_table->setItem(row, 2, new QTableWidgetItem(pos));                                  // Positie
        pan_table->setItem(row, 3, new QTableWidgetItem(QString("%1").arg(obj.size)));          // Diameter
        pan_table->setItem(row, 4, new QTableWidgetItem(dir));                                  // Richting
        pan_table->setItem(row, 5, new QTableWidgetItem(QString("%1").arg(obj.speed)));         // Snelheid
        pan_table->setItem(row, 6, new QTableWidgetItem(QString("%1").arg(obj.acceleration)));  // Versnelling

        row++;
    }   
}

void GUIApplication::update2d(vector<Object2D> objects){}
void GUIApplication:: updateStatistics(StatisticsObject obj){}

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

//////////

void GUIApplication::rotationChangeX1(int x)
{
    SettingSingleton *ds = ds->getInstance();
    struct rotationSettings rs = ds->getRotate2();
    rs.x = (float)(x / 1000.0);
    ds->setRotate2(rs);
}
void GUIApplication::rotationChangeY1(int y)
{
    SettingSingleton *ds = ds->getInstance();
    struct rotationSettings rs = ds->getRotate2();
    rs.y = (float)(y / 1000.0);
    ds->setRotate2(rs);
}
void GUIApplication::rotationChangeZ1(int z)
{
    SettingSingleton *ds = ds->getInstance();
    struct rotationSettings rs = ds->getRotate2();
    rs.z = (float)(z / 1000.0);
    ds->setRotate2(rs);
}
void GUIApplication::positionChangeX1(int x)
{
    SettingSingleton *ds = ds->getInstance();
    struct moveSettings rs = ds->getMove2();
    rs.x = (float)(x / 1000.0);
    ds->setMove2(rs);
}
void GUIApplication::positionChangeY1(int y)
{
    SettingSingleton *ds = ds->getInstance();
    struct moveSettings rs = ds->getMove2();
    rs.y = (float)(y / 1000.0);
    ds->setMove2(rs);
}
void GUIApplication::positionChangeZ1(int z)
{
    SettingSingleton *ds = ds->getInstance();
    struct moveSettings rs = ds->getMove2();
    rs.z = (float)(z / 1000.0);
    ds->setMove2(rs);
}

////////////

void GUIApplication::filterChangex(int v)
{
    SettingSingleton *ds = ds->getInstance();
    struct filterSettings fs = ds->getFilter();
    fs.x = (float)(v / 1000.0);
    ds->setFilter(fs);
}
void GUIApplication::filterChangex1(int v)
{
    SettingSingleton *ds = ds->getInstance();
    struct filterSettings fs = ds->getFilter();
    fs.x1 = (float)(v / 1000.0);
    ds->setFilter(fs);
}
void GUIApplication::filterChangey(int v)
{
    SettingSingleton *ds = ds->getInstance();
    struct filterSettings fs = ds->getFilter();
    fs.y = (float)(v / 1000.0);
    ds->setFilter(fs);
}
void GUIApplication::filterChangey1(int v)
{
    SettingSingleton *ds = ds->getInstance();
    struct filterSettings fs = ds->getFilter();
    fs.y1 = (float)(v / 1000.0);
    ds->setFilter(fs);
}
void GUIApplication::filterChangez(int v)
{
    SettingSingleton *ds = ds->getInstance();
    struct filterSettings fs = ds->getFilter();
    fs.z = (float)(v / 1000.0);
    ds->setFilter(fs);
}
void GUIApplication::filterChangez1(int v)
{
    SettingSingleton *ds = ds->getInstance();
    struct filterSettings fs = ds->getFilter();
    fs.z1 = (float)(v / 1000.0);
    ds->setFilter(fs);
}

void printXYZ(moveSettings ms) {
    std::cout << "Move box : \n";
    std::cout << "x = " << ms.x << ", y = " << ms.y << ", z = " << ms.z << "\n";
}
void printXYZ(rotationSettings rs) {
    std::cout << "Rotation box : \n";
    std::cout << "x = " << rs.x << ", y = " << rs.y << ", z = " << rs.z << "\n";
}

void printXYZ(filterSettings fs) {
    std::cout << "Filter box : \n";
    std::cout << "x = " << fs.x << ", x1 = " << fs.x1 << "\n";
    std::cout << "y = " << fs.y << ", y1 = " << fs.y1 << "\n";
    std::cout << "z = " << fs.z << ", z1 = " << fs.z1 << std::endl;
}

void GUIApplication::setConfiguring(){
    std::cout << "Stopped Configure" << std::endl;

    printXYZ(SettingSingleton::getInstance()->getMove());
    printXYZ(SettingSingleton::getInstance()->getMove2());
    printXYZ(SettingSingleton::getInstance()->getRotate());
    printXYZ(SettingSingleton::getInstance()->getRotate2());
    printXYZ(SettingSingleton::getInstance()->getFilter());


    GUIData::getInstance()->configuring = false;
    return;
}

