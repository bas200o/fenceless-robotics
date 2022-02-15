#include "../include/GUIData.hpp"
#include <math.h>

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

        //obj.direction.x = vo.direction.x;
        //obj.direction.y = vo.direction.y;

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

    for(FoundObject obj : data.getObjects()){
        std::tuple<float, float, float> center = obj.getCenterMass();
        vec3 vec = {round((get<0>(center)*100))/100, round((get<1>(center)*100))/100, round((get<2>(center)*100))/100};
        int id = obj.getIdentificationNumber();
        double fSpeed;
        if(obj.getSpeed() > 0.00001){
        fSpeed = obj.getSpeed();
        }
        else{
            fSpeed = 0;
        }

        VisualObject vs = {id, -1, vec, round(obj.getSize()*100)/100, obj.getDirectionHor(), obj.getDirectionVer(), obj.getSpeed(), -1};
        //std::cout << (int)obj.getSpeed()*10000000000.0f << std::endl;
        vos.push_back(vs);

        // int showTime;
        // vec3 position;
        // double size;
        // vec3 direction;
        // double speed;
        // double acceleration;
    }

    sort(vos.begin(), vos.end(), [] (VisualObject o1, VisualObject o2) {
        vec3 zero; zero.x = 0; zero.y = 0; zero.z = 0;
        return sqrt(pow(o1.position.x,2)+ pow(o1.position.y,2)+ pow(o1.position.z,2)) < 
                sqrt(pow(o2.position.x,2)+ pow(o2.position.y,2)+ pow(o2.position.z,2));
    });

    return setObjects(vos);
};

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