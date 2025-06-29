#pragma once

#include <glm/glm.hpp>
#include"Command.h"
#include<memory>
namespace dae
{
    class GameObject;

    class TestCommand : public Command
    {
    public:
        TestCommand();
        virtual void Execute() override;
        virtual void Undo() override;

    private:
    };
}

