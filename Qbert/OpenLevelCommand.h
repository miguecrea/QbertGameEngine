
#pragma once
#include "Command.h"
#include <glm/glm.hpp>
#include<vector>
#include<memory>

namespace dae
{

    class GameObject;
    class ChangeModeCommand;
    class Keyboard;
    class Scene;
    class InputManager;

    class OpenLevelCommand : public Command
    {
    public:

        explicit OpenLevelCommand(std::vector<std::shared_ptr<dae::GameObject>>TextGameObjects,ChangeModeCommand * command);
        virtual ~OpenLevelCommand() = default;

        virtual void Execute() override;
        void AddKeyBindOnePerson(dae::Keyboard* keyboard, dae::Scene* scene, dae::InputManager& input);
        virtual void Undo() override;

    protected:

        std::vector<std::shared_ptr<dae::GameObject>> m_TextGameObjects;
        ChangeModeCommand * m_ChangeModeCommand;
    };
}

