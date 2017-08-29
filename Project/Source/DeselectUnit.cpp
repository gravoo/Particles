#include <DeselectUnit.hpp>
#include <GameBuildUnit.hpp>
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

