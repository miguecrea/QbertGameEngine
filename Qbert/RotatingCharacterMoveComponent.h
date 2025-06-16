#pragma once

#include"Component.h"
#include<memory>

namespace dae
{
    class GameObject;
    class RenderComponent;

    class RotatingCharacterMoveComponent final : public Component
    {
    public:

        RotatingCharacterMoveComponent();
        virtual ~RotatingCharacterMoveComponent() = default;
        RotatingCharacterMoveComponent(const RotatingCharacterMoveComponent& other) = default;
        RotatingCharacterMoveComponent(RotatingCharacterMoveComponent&& other) = default;
        RotatingCharacterMoveComponent& operator=(const RotatingCharacterMoveComponent& other) = default;
        RotatingCharacterMoveComponent& operator=(RotatingCharacterMoveComponent&& other) = default;

        void  BeginPlay();
        void  Update() override;
        void  Render() override;

        bool m_Active = false;
        void SwapActive();
        void SetWaitingTime(int waitingTime);
        float m_Speed = 20.f;
        void SetSpeed(float newSpeed);
    private:

        int m_WaitingTime = 0;
        void OnTimerStarted(std::shared_ptr<dae::GameObject> gameObect);
        bool m_StartCounter = false;
        float m_CollisionTimer = 0.f;
        std::shared_ptr<GameObject> m_CollideObject;
        std::shared_ptr<dae::RenderComponent> m_RenderComponent;
    };
}