#include "../include/GUIData.hpp"

GUIData::GUIData()
{
    
}

/*GUIData::GUIData(QList<Object2D> view2dObjects, 
    QList<VisualObject> tableObjects, 
    StatisticsObject statsObject)
{
    view2d = view2dObjects;
    table = tableObjects;
    stats = statsObject;    
}*/

void GUIData::updateTable(Information3D newData)
{
    // TODO: Process information data

    Q_EMIT changed_table(table);
}

void GUIData::updateTable(QList<VisualObject> newTable)
{
    table = newTable;
    Q_EMIT changed_table(table);
}

#pragma region TODO FUNCTION

void GUIData::changed_2d(QList<Object2D> objects) {}
void GUIData::changed_table(QList<VisualObject> objects) {}
void GUIData::changed_statistics(StatisticsObject object) {}

#pragma endregion TODO FUNCTION
