#pragma once


#pragma once
#include "Command.h"
#include <glm/glm.hpp>

namespace dae
{
    class Command2D : public Command
    {
    public:
        explicit Command2D() = default;
        virtual ~Command2D() = default;

        virtual void Execute() override;
        virtual void Undo() override;
        void SetValue(const glm::vec2& value);

    protected:
        glm::vec2 m_Value{};
    };
}

