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

    // Pannel Cancel config button
    auto pancake = new QPushButton("Stop configuring");
    connect(pancake, &QPushButton::released, this, GUIApplication::setConfiguring);

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

    layout = new QGridLayout(this);

    layout->addWidget(pan_view2d, 0, 0);
    layout->addWidget(pancake, 0, 1);
    layout->addWidget(pan_statistics, 0, 2);
    layout->addWidget(pan_table, 1, 0, 1, 3);

    for (size_t i = 0; i < CameraConnector::getInstance()->getConnectedRSCameras().size(); i++)
    {
        addPclWindow(i);
    }
}

void GUIApplication::addPclWindow(int id) {
    QWidget* window = new QWidget;
    window->setMinimumWidth(500);
    QGridLayout *window_layout = new QGridLayout(window);

    moveSettings ms =  SettingSingleton::getInstance()->getMove(id);    
    rotationSettings rs =  SettingSingleton::getInstance()->getRotate(id);
    rotationSettings rs1 =  SettingSingleton::getInstance()->getRotate2(id);
    filterSettings fs = SettingSingleton::getInstance()->getFilter(id);

    static int privInt = id;

    QSlider* sliderMvX = getDefaultSlider(ms.x * 1000);
    GUIApplication::moveXSliders.push_back(sliderMvX);
    connect(sliderMvX, &QSlider::valueChanged, this, [this]{ GUIApplication::positionChangeX(privInt); });
    QSlider* sliderMvY = getDefaultSlider(ms.y * 1000);
    GUIApplication::moveYSliders.push_back(sliderMvY);
    connect(sliderMvY, &QSlider::valueChanged, this, [this]{ GUIApplication::positionChangeY(privInt); });
    QSlider* sliderMvZ = getDefaultSlider(ms.z * 1000);
    GUIApplication::moveZSliders.push_back(sliderMvZ);
    connect(sliderMvZ, &QSlider::valueChanged, this, [this]{ GUIApplication::positionChangeZ(privInt); });

    QSlider* sliderRtX = getDefaultSlider(rs.x * 1000);
    GUIApplication::rotateXSliders.push_back(sliderRtX);
    connect(sliderRtX, &QSlider::valueChanged, this, [this]{ GUIApplication::rotationChangeX(privInt); });
    QSlider* sliderRtY = getDefaultSlider(rs.y * 1000);
    GUIApplication::rotateYSliders.push_back(sliderRtY);
    connect(sliderRtY, &QSlider::valueChanged, this, [this]{ GUIApplication::rotationChangeY(privInt); });
    QSlider* sliderRtZ = getDefaultSlider(rs.z * 1000);
    GUIApplication::rotateZSliders.push_back(sliderRtZ);
    connect(sliderRtZ, &QSlider::valueChanged, this, [this]{ GUIApplication::rotationChangeZ(privInt); });
    QSlider* sliderRtX1 = getDefaultSlider(rs1.x * 1000);
    GUIApplication::rotate1XSliders.push_back(sliderRtX1);
    connect(sliderRtX1, &QSlider::valueChanged, this, [this]{ GUIApplication::rotationChangeX1(privInt); });
    QSlider* sliderRtY1 = getDefaultSlider(rs1.y * 1000);
    GUIApplication::rotate1YSliders.push_back(sliderRtY1);
    connect(sliderRtY1, &QSlider::valueChanged, this, [this]{ GUIApplication::rotationChangeY1(privInt); });
    QSlider* sliderRtZ1 = getDefaultSlider(rs1.z * 1000);
    GUIApplication::rotate1ZSliders.push_back(sliderRtZ1);
    connect(sliderRtZ1, &QSlider::valueChanged, this, [this]{ GUIApplication::rotationChangeZ1(privInt); });

    QSlider* sliderFX = getDefaultSlider(fs.x * 1000);
    GUIApplication::filterXSliders.push_back(sliderFX);
    connect(sliderFX, &QSlider::valueChanged, this, [this]{ GUIApplication::filterChangex(privInt); });
    QSlider* sliderFX1 = getDefaultSlider(fs.x1);
    GUIApplication::filter1XSliders.push_back(sliderFX1);
    connect(sliderFX1, &QSlider::valueChanged, this, [this]{ GUIApplication::filterChangex1(privInt); });
    QSlider* sliderFY = getDefaultSlider(fs.y * 1000);
    GUIApplication::filterYSliders.push_back(sliderFY);
    connect(sliderFY, &QSlider::valueChanged, this, [this]{ GUIApplication::filterChangey(privInt); });
    QSlider* sliderFY1 = getDefaultSlider(fs.y1 * 1000);
    GUIApplication::filter1YSliders.push_back(sliderFY1);
    connect(sliderFY1, &QSlider::valueChanged, this, [this]{ GUIApplication::filterChangey1(privInt); });
    QSlider* sliderFZ = getDefaultSlider(fs.z * 1000);
    GUIApplication::filterZSliders.push_back(sliderFZ);
    connect(sliderFZ, &QSlider::valueChanged, this, [this]{ GUIApplication::filterChangez(privInt); });
    QSlider* sliderFZ1 = getDefaultSlider(fs.z1 * 1000);
    GUIApplication::filter1ZSliders.push_back(sliderFZ1);
    connect(sliderFZ1, &QSlider::valueChanged, this, [this]{ GUIApplication::filterChangez1(privInt); });

    QCheckBox* visable = new QCheckBox();
    visable->setChecked(SettingSingleton::getInstance()->getVisable(id));
    GUIApplication::checkBoxes.push_back(visable);
    connect(visable, &QCheckBox::stateChanged, this, [this]{ GUIApplication::checkBoxClicked(privInt); });

    stringstream ss;
    ss << "Point cloud " << id+1;

    QLabel* title = new QLabel(ss.str().c_str());
    QLabel* vis = new QLabel("Visable: ");
    QLabel* mx = new QLabel("move x");
    QLabel* my = new QLabel("move y");
    QLabel* mz = new QLabel("move z");
    QLabel* rx = new QLabel("rotate x");
    QLabel* ry = new QLabel("rotate y");
    QLabel* rz = new QLabel("rotate z");
    QLabel* fx = new QLabel("filter x");
    QLabel* fy = new QLabel("filter y");
    QLabel* fz = new QLabel("filter z");
 
    window_layout->addWidget(title, 1, 0);
    window_layout->addWidget(vis, 1, 1);
    window_layout->addWidget(visable, 1, 2);

    window_layout->addWidget(mx, 2, 0, 1, 1);
    window_layout->addWidget(sliderMvX, 2, 1, 1, 2);
    
    window_layout->addWidget(my, 3, 0, 1, 1);
    window_layout->addWidget(sliderMvY, 3, 1, 1, 2);
    
    window_layout->addWidget(mz, 4, 0, 1, 1);
    window_layout->addWidget(sliderMvZ, 4, 1, 1, 2);
    
    window_layout->addWidget(rx, 5, 0, 1, 1);
    window_layout->addWidget(sliderRtX, 5, 1, 1, 1);
    window_layout->addWidget(sliderRtX1, 5, 2, 1, 1);
    
    window_layout->addWidget(ry, 6, 0, 1, 1);
    window_layout->addWidget(sliderRtY, 6, 1, 1, 1);
    window_layout->addWidget(sliderRtY1, 6, 2, 1, 1);

    window_layout->addWidget(rz, 7, 0, 1, 1);
    window_layout->addWidget(sliderRtZ, 7, 1, 1, 1);
    window_layout->addWidget(sliderRtZ1, 7, 2, 1, 1);

    window_layout->addWidget(fx, 9, 0, 1, 1);
    window_layout->addWidget(sliderFX, 9, 1, 1, 1);
    window_layout->addWidget(sliderFX1, 9, 2, 1, 1);
    
    window_layout->addWidget(fy, 10, 0, 1, 1);
    window_layout->addWidget(sliderFY, 10, 1, 1, 1);
    window_layout->addWidget(sliderFY1, 10, 2, 1, 1);
    
    window_layout->addWidget(fz, 11, 0, 1, 1);
    window_layout->addWidget(sliderFZ, 11, 1, 1, 1);
    window_layout->addWidget(sliderFZ1, 11, 2, 1, 1);
    
    window->show();
} 

QSlider* GUIApplication::getDefaultSlider(int val, int min, int max) {
    QSlider* slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(min);
    slider->setMaximum(max);
    slider->setValue(val);
    return slider;
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

void GUIApplication::rotationChangeX(int id)
{
    SettingSingleton *ds = ds->getInstance();
    struct rotationSettings rs = ds->getRotate(id);
    rs.x = (float)(GUIApplication::rotateXSliders.at(id)->value() / 1000.0);
    ds->setRotate(id, rs);
}

void GUIApplication::rotationChangeY(int id)
{
    SettingSingleton *ds = ds->getInstance();
    struct rotationSettings rs = ds->getRotate(id);
    rs.y = (float)(GUIApplication::rotateYSliders.at(id)->value() / 1000.0);
    ds->setRotate(id, rs);
}
void GUIApplication::rotationChangeZ(int id)
{
    SettingSingleton *ds = ds->getInstance();
    struct rotationSettings rs = ds->getRotate(id);
    rs.z = (float)(GUIApplication::rotateZSliders.at(id)->value() / 1000.0);
    ds->setRotate(id, rs);
}
void GUIApplication::positionChangeX(int id)
{
    SettingSingleton *ds = ds->getInstance();
    struct moveSettings rs = ds->getMove(id);
    rs.x = (float)(GUIApplication::moveXSliders.at(id)->value() / 1000.0);
    ds->setMove(id, rs);
}
void GUIApplication::positionChangeY(int id)
{
    SettingSingleton *ds = ds->getInstance();
    struct moveSettings rs = ds->getMove(id);
    rs.y = (float)(GUIApplication::moveYSliders.at(id)->value() / 1000.0);
    ds->setMove(id, rs);
}
void GUIApplication::positionChangeZ(int id)
{
    SettingSingleton *ds = ds->getInstance();
    struct moveSettings rs = ds->getMove(id);
    rs.z = (float)(GUIApplication::moveZSliders.at(id)->value() / 1000.0);
    ds->setMove(id, rs);
}

void GUIApplication::rotationChangeX1(int id)
{
    SettingSingleton *ds = ds->getInstance();
    struct rotationSettings rs = ds->getRotate2(id);
    rs.x = (float)(GUIApplication::rotate1XSliders.at(id)->value() / 1000.0);
    ds->setRotate2(id, rs);
}
void GUIApplication::rotationChangeY1(int id)
{
    SettingSingleton *ds = ds->getInstance();
    struct rotationSettings rs = ds->getRotate2(id);
    rs.y = (float)(GUIApplication::rotate1YSliders.at(id)->value() / 1000.0);
    ds->setRotate2(id, rs);
}
void GUIApplication::rotationChangeZ1(int id)
{
    SettingSingleton *ds = ds->getInstance();
    struct rotationSettings rs = ds->getRotate2(id);
    rs.z = (float)(GUIApplication::rotate1ZSliders.at(id)->value() / 1000.0);
    ds->setRotate2(id, rs);
}

void GUIApplication::filterChangex(int id)
{
    SettingSingleton *ds = ds->getInstance();
    struct filterSettings fs = ds->getFilter(id);
    fs.x = (float)(GUIApplication::filterXSliders.at(id)->value() / 1000.0);
    ds->setFilter(id, fs);
}
void GUIApplication::filterChangex1(int id)
{
    SettingSingleton *ds = ds->getInstance();
    struct filterSettings fs = ds->getFilter(id);
    fs.x1 = (float)(GUIApplication::filterYSliders.at(id)->value() / 1000.0);
    ds->setFilter(id, fs);
}
void GUIApplication::filterChangey(int id)
{
    SettingSingleton *ds = ds->getInstance();
    struct filterSettings fs = ds->getFilter(id);
    fs.y = (float)(GUIApplication::filterZSliders.at(id)->value() / 1000.0);
    ds->setFilter(id, fs);
}
void GUIApplication::filterChangey1(int id)
{
    SettingSingleton *ds = ds->getInstance();
    struct filterSettings fs = ds->getFilter(id);
    fs.y1 = (float)(GUIApplication::filter1YSliders.at(id)->value() / 1000.0);
    ds->setFilter(id, fs);
}
void GUIApplication::filterChangez(int id)
{
    SettingSingleton *ds = ds->getInstance();
    struct filterSettings fs = ds->getFilter(id);
    fs.z = (float)(GUIApplication::filterZSliders.at(id)->value() / 1000.0);
    ds->setFilter(id, fs);
}
void GUIApplication::filterChangez1(int id)
{
    SettingSingleton *ds = ds->getInstance();
    struct filterSettings fs = ds->getFilter(id);
    fs.z1 = (float)(GUIApplication::filter1ZSliders.at(id)->value() / 1000.0);
    ds->setFilter(id, fs);
}

void GUIApplication::checkBoxClicked(int id) {
    SettingSingleton::getInstance()->setVisable(id, GUIApplication::checkBoxes.at(id)->isChecked());
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

    // printXYZ(SettingSingleton::getInstance()->getMove());
    // printXYZ(SettingSingleton::getInstance()->getMove2());
    // printXYZ(SettingSingleton::getInstance()->getRotate());
    // printXYZ(SettingSingleton::getInstance()->getRotate2());
    // printXYZ(SettingSingleton::getInstance()->getFilter());


    GUIData::getInstance()->configuring = false;
    return;
}