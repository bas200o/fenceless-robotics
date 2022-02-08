#include "../include/SettingSingleton.hpp"

std::vector<rotationSettings> rs_cloud;
std::vector<rotationSettings> rs2_cloud;
std::vector<filterSettings> fs_cloud;
std::vector<moveSettings> ms_cloud;
std::vector<moveSettings> ms2_cloud;
std::vector<bool> vs_cloud;
std::vector<rgbSettings> rgbs_cloud;


SettingSingleton *SettingSingleton::instance;

SettingSingleton::SettingSingleton()
{

    rs_cloud.push_back({0.701, 0.165, -0.028});
    rs2_cloud.push_back( {0, 0.629, -0.062});
    ms_cloud.push_back({-0.212, 1.113, -0.079});
    ms2_cloud.push_back({0.0, 0.0, 0.0});//unnececary
    fs_cloud.push_back({0.028, 1.086, 0.028, 3.714, -0.142, 1.429});

    rs_cloud.push_back({0.879, 0.936, -0.709});
    rs2_cloud.push_back( {0.057, -1.086, -0.057});
    ms_cloud.push_back({0.848, 1.192, -0.371});
    ms2_cloud.push_back({0.0, 0.0, 0.0});//unnececary
    fs_cloud.push_back({0.085, 1.086, 0.028, 10.0, -4, 1.143});
    


    vs_cloud.push_back(true);
    vs_cloud.push_back(true);

    rgbs_cloud.push_back({255, 255, 255});
    rgbs_cloud.push_back({255, 255, 255});
}

SettingSingleton::~SettingSingleton()
{
}

rotationSettings SettingSingleton::getRotate(int id)
{
    return rs_cloud[id];
}

void SettingSingleton::setRotate(int id, rotationSettings ndata)
{
    rs_cloud[id] = ndata;
}

filterSettings SettingSingleton::getFilter(int id)
{
    return fs_cloud[id];
}

void SettingSingleton::setFilter(int id, filterSettings ndata)
{
    fs_cloud[id] = ndata;
}

moveSettings SettingSingleton::getMove(int id)
{
    return ms_cloud[id];
}

void SettingSingleton::setMove(int id, moveSettings ndata)
{
    ms_cloud[id] = ndata;
}


rotationSettings SettingSingleton::getRotate2(int id)
{
    return rs2_cloud[id];
}

void SettingSingleton::setRotate2(int id, rotationSettings ndata)
{
    rs2_cloud[id] = ndata;
}

moveSettings SettingSingleton::getMove2(int id)
{
    return ms2_cloud[id];
}

void SettingSingleton::setMove2(int id, moveSettings ndata)
{
    ms2_cloud[id] = ndata;
}

bool SettingSingleton::getVisable(int id) {
    return vs_cloud[id];
}

void SettingSingleton::setVisable(int id, bool visable) {
    vs_cloud[id] = visable;
}

rgbSettings SettingSingleton::getRgb(int id) {
    return rgbs_cloud[id];
}

void SettingSingleton::setRgb(int id, rgbSettings data) {
    rgbs_cloud[id] = data;
}

SettingSingleton *SettingSingleton::getInstance()
{
    if (!instance)
        instance = new SettingSingleton();
    return instance;
}