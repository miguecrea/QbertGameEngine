
#pragma once
#include "Command.h"
#include<string>
#include<vector>
#include"memory"
namespace dae
{


    enum class Direction
    {
        RIGHT,
        LEFT,
        UP,
        DOWN
    };

    class GameObject;
    class ChangeSelectionCommand final : public Command
    {
    public:
        ChangeSelectionCommand(std::vector<std::shared_ptr<dae::GameObject>> & obejcts,int currentActiveTile, Direction keyDirection);
        void Execute() override;
        void GetCharacterBasedOnDirection();
        virtual void Undo() override;

    private:
        const int ROWS{3};
        const int COLUMNS{9};
        int m_currentActiveTile;
        std::vector<std::shared_ptr<dae::GameObject>> m_objects;
        Direction m_KeyDirection;
        int Clamp(int number ,int min, int max);
    };
}
