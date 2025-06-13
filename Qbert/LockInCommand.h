
#pragma once
#include "Command.h"
#include<string>
#include<vector>
#include"memory"
namespace dae
{
    class GameObject;
    class LockInCommand final : public Command
    {
    public:
        LockInCommand(std::vector<std::shared_ptr<dae::GameObject>> & obejcts);
        void Execute() override;
        virtual void Undo() override;
    private:
        std::vector<std::shared_ptr<dae::GameObject>> m_objects;
    };
}

