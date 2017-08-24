#pragma once
#include<ICommand.hpp>
#include<memory>


class GameBuildUnit;

class DeselectUnit : public ICommand
{
public:
    DeselectUnit(std::shared_ptr<GameBuildUnit> selectedUnit);
    void execute() override;
private:
    std::shared_ptr<GameBuildUnit> selectedUnit;
};
