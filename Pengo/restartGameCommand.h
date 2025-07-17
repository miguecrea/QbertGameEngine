#pragma once

#include <glm/glm.hpp>
#include"Command.h"
#include<memory>
namespace dae
{
    class GameObject;
    class PengoComponent;

    class restartGameCommand : public Command
    {
    public:
        restartGameCommand();
        virtual void Execute() override;
        virtual void Undo() override;
        int m_MaxLives = 3;

    private:

    };

}