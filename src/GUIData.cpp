#include "../include/GUIData.hpp"

GUIData::GUIData()
{
    view2d_busy, view2d_newdata = false;
    table_busy, table_newdata = false;
    stats_busy, stats_newdata = false;
}

GUIData* GUIData::instance = NULL;

GUIData* GUIData::getInstance()
{
    if(instance == NULL)
    {
        instance = new GUIData();
    }

    return instance;
}

int GUIData::setObjects(vector<VisualObject> objects)
{
    int success = 1;

    // Table
    if(!table_busy)
    {
        table_busy = true;

        table = objects;

        table_busy = false;
        table_newdata = true;
    } else
    {
        success = 0;
    }

    // View2D
    vector<Object2D> objs;
    for(VisualObject vo : objects)
    {
        Object2D obj;

        obj.position.x = vo.position.x;
        obj.position.y = vo.position.y;

        obj.direction.x = vo.direction.x;
        obj.direction.y = vo.direction.y;

        objs.push_back(obj);
    }

    if(!view2d_busy)
    {
        view2d_busy = true;

        view2d = objs;

        view2d_busy = false;
        view2d_newdata = true;
    } else
    {
        success = 0;
    }
    
    return success;
}

int GUIData::setObjects(Information3D data)
{
    vector<VisualObject> vos;

    // TODO: Process Information3D

    return setObjects(vos);
}

int GUIData::setStatistics(StatisticsObject newStats)
{
    if(stats_busy)
        return 0; // Busy, try again later

    stats_busy = true;

    stats = newStats;

    stats_busy = false;
    stats_newdata = true;
    return 1;
}

vector<Object2D> GUIData::getView2D()
{
    if(view2d_busy)
        return vector<Object2D>(); // Empty vector indicates bad result

    view2d_newdata = false;
    return view2d;
}
vector<VisualObject> GUIData::getTable()
{
    if(table_busy)
        return vector<VisualObject>(); // Empty vector indicates bad result
    
    table_newdata = false;
    return table;
}
StatisticsObject GUIData::getStats()
{
    if(stats_busy)
        return StatisticsObject(); // Empty object indicates bad result

    stats_newdata = false;
    return stats;
}

DataFlags GUIData::getDataFlags()
{
    DataFlags res;
    res.view2d = view2d_newdata;
    res.visualobject = table_newdata;
    res.stats = stats_newdata;
    return res;
}