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
        BreakMoveTileCommand();
        virtual void Execute() override;
        virtual void Undo() override;

    private:

    };

}