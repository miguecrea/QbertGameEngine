#pragma once


#include <glm/glm.hpp>
#include"Command.h"
#include<memory>
namespace dae
{
    class GameObject;

    class BreakMoveTileCommand : public Command
    {
    public:
        BreakMoveTileCommand(std::shared_ptr<dae::GameObject> pGameObject);
        virtual void Execute() override;
        virtual void Undo() override;

    private:
        std::shared_ptr<dae::GameObject> m_Pengo;

    };

}