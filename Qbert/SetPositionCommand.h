#pragma once
#include "Command.h"
#include <glm/glm.hpp>
#include<memory>


namespace dae
{
    class GameObject;
    class RenderComponent;
    class JumpAnimationComponent;

    class SetPositionCommand final : public Command
    {
    public:
        SetPositionCommand(GameObject* pGameObject, const glm::vec3& direction,std::shared_ptr<dae::RenderComponent> renderComponent, int Direction);
        void Execute() override;
        void Undo() override;
    private:
        GameObject* m_pGameObject;
        glm::vec3 m_OldPosition;
        glm::vec3 m_Direction;
        int m_QbertState;
        std::shared_ptr<dae::RenderComponent> m_renderComponent;
        std::shared_ptr<dae::JumpAnimationComponent> m_JumpAnimation;
        float m_JumpDuration = 0.4f;
        float m_Volume = 0.4f;
    };
}

