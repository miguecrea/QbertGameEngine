#pragma once
#include "Component.h"
#include"GameObject.h"
#include"DelegateBase.h"
namespace dae
{
    class GameObject;
    class TimerAndInputComponent;
    class FreeFallComponent;
    class TagComponent;
    class CollisionComponent;
    class CollisionWithComponent;
    class CollsionResponse final : public Component
    {
    public:

        CollsionResponse();    /// vector
        virtual ~CollsionResponse() = default;
        CollsionResponse(const  CollsionResponse & other) = default;
        CollsionResponse(CollsionResponse&& other) = default;
        CollsionResponse& operator=(const CollsionResponse & other) = default;
        CollsionResponse& operator=(CollsionResponse&& other) = default;


        virtual void BeginPlay() override;
        void GetComponents();
        void  Render() override;
        void  Update() override;
        

        void OnCollision(std::string selftag, std::string CollidedObjecTag);

        std::shared_ptr<dae::GameObject> m_CollidedObjectReference;
        void HandleInsibleRectCollision(std::string CollidedObjecTag);
        void HandleBottomRectCollision(std::string CollidedObjecTag);
        void HandlePlatformCollision();
        void HandleRotatingCharacterCollision();

        MulticastDelegate <std::shared_ptr<dae::GameObject>> m_OnTimerStarted;


        bool Execute = true;
    private:

        std::shared_ptr<dae::CollisionWithComponent> m_CollisionWithComponent;
        std::shared_ptr<dae::TagComponent> m_TagComponent;
        std::shared_ptr<dae::TagComponent> m_CollidingObjectTagComponent;
        std::shared_ptr<dae::CollisionComponent> m_CollisionComponent;
        std::shared_ptr<dae::TimerAndInputComponent> m_TimeAndInputComponent;
        std::shared_ptr<dae::FreeFallComponent> m_FreFallComponent;

        float InitialPosX{ 98 };
        float InitialPosY{ 87 };

        float InitialPosXTutorial{ 96 };
        float InitialPosYTutorial{ 59 };

        bool m_StartCounter = false;

        float m_CollisionTimer = 0.f;
        



        



    };
}