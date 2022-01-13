#pragma once

using namespace std;

struct rotationSettings
{
    float x, y, z;
};

struct moveSettings
{
    float x, y, z;
};

struct filterSettings
{
    float x, x1, y, y1, z, z1;
};

class SettingSingleton
{
public:
    static SettingSingleton *instance;
    rotationSettings data;

    // Private constructor so that no objects can be created.
    SettingSingleton();
    ~SettingSingleton();

    static SettingSingleton *getInstance();

    rotationSettings getRotate();
    void setRotate(rotationSettings data);
    moveSettings getMove();
    void setMove(moveSettings data);
    filterSettings getFilter();
    void setFilter(filterSettings data);
};
