#pragma once
#include "Command.h"

namespace dae
{
    class Command1D : public Command
    {
    public:
        explicit Command1D();
        virtual ~Command1D() = default;

        virtual void Execute() override;

        void SetValue(float value);

    protected:
        float m_Value{};
    };
}

