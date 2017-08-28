#include<DeselectUnit.hpp>
#include<GameBuildUnit.hpp>
#include<iostream>
DeselectUnit::DeselectUnit(std::shared_ptr<GameBuildUnit> selectedUnit) : selectedUnit(selectedUnit)
{
}

void DeselectUnit::execute()
{
    if(selectedUnit)
    {
        selectedUnit->deselectUnit();
    }
}

