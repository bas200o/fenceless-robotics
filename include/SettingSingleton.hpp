/*Singleton used to keep track of settings for translating the camera's 
*/
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

    rotationSettings getRotate2();
    void setRotate2(rotationSettings data);
    moveSettings getMove2();
    void setMove2(moveSettings data);

    filterSettings getFilter();
    void setFilter(filterSettings data);
};
