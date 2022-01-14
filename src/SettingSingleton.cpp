#include "../include/SettingSingleton.hpp"

rotationSettings rs;
filterSettings fs;
moveSettings ms;
SettingSingleton *SettingSingleton::instance;

SettingSingleton::SettingSingleton()
{
    rs = {0.0, 0.0, 0.0};
    fs = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    ms = {0.0, 0.0, 0.0};
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

SettingSingleton *SettingSingleton::getInstance()
{
    if (!instance)
        instance = new SettingSingleton();
    return instance;
}