/*Singleton used to keep track of settings for translating the camera's 
*/
#pragma once

#include <vector>

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

    rotationSettings getRotate(int id);
    void setRotate(int id, rotationSettings data);
    moveSettings getMove(int id);
    void setMove(int id, moveSettings data);

    rotationSettings getRotate2(int id);
    void setRotate2(int id, rotationSettings data);
    moveSettings getMove2(int id);
    void setMove2(int id, moveSettings data);

    filterSettings getFilter(int id);
    void setFilter(int id, filterSettings data);

    bool getVisable(int id);
    void setVisable(int id, bool visable);
};
