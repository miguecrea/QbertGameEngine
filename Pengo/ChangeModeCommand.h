#pragma once

#include "Command.h"
#include<vector>
#include <memory> 
#include"Command2D.h"

namespace dae
{
    class GameObject;

    class ChangeModeCommand final : public Command2D
    {
    public:
        ChangeModeCommand(std::vector<std::shared_ptr<dae::GameObject>>TextGameObjects);
        void Execute() override;
        void ChangeNextOne();
        void Undo() override;

        std::unique_ptr<ChangeModeCommand> Clone() const{
            return std::make_unique<ChangeModeCommand>(*this);
        }

        int GetCurrentIndex();

    private:
        std::vector<std::shared_ptr<dae::GameObject>> m_TextGameObejects;
        int m_Index = 0;
        int m_VectorSize = 0;
        bool m_CanExecute = true;
        float m_Counter = 0.f;
        float m_TimeUntilCallingAgain = 0.3f;

    };
}

