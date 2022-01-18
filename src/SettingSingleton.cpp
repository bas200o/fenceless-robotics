#include "../include/SettingSingleton.hpp"

rotationSettings rs;
rotationSettings rs2;
filterSettings fs;
moveSettings ms;
moveSettings ms2;
SettingSingleton *SettingSingleton::instance;

SettingSingleton::SettingSingleton()
{
    rs = {0.718, 0.156, -0.065};
    fs = {-10.0, 10.0, -10.0, 10.0, -10.0, 10.0};
    ms = {0.0, 1.129, 0.0};
    rs2 = {0.0, 0.0, 0.0};
    ms2 = {0.0, 0.0, 0.0};
}

SettingSingleton::~SettingSingleton()
{
}

rotationSettings SettingSingleton::getRotate()
{
    return rs;
}
void SettingSingleton::setRotate(rotationSettings ndata)
{
    rs = ndata;
}

filterSettings SettingSingleton::getFilter()
{
    return fs;
}
void SettingSingleton::setFilter(filterSettings ndata)
{
    fs = ndata;
}

moveSettings SettingSingleton::getMove()
{
    return ms;
}
void SettingSingleton::setMove(moveSettings ndata)
{
    ms = ndata;
}


rotationSettings SettingSingleton::getRotate2()
{
    return rs2;
}
void SettingSingleton::setRotate2(rotationSettings ndata)
{
    rs2 = ndata;
}
moveSettings SettingSingleton::getMove2()
{
    return ms2;
}
void SettingSingleton::setMove2(moveSettings ndata)
{
    ms2 = ndata;
}

SettingSingleton *SettingSingleton::getInstance()
{
    if (!instance)
        instance = new SettingSingleton();
    return instance;
}