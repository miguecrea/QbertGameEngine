#pragma once


#include"Component.h"
#include"memory"
namespace dae
{
    class GameObject;

    class CurseQbertComponent final : public Component
    {
    public:


        CurseQbertComponent(std::shared_ptr<dae::GameObject> Qbert);    /// vector  //time to update 
        virtual ~CurseQbertComponent() = default;
        CurseQbertComponent(const CurseQbertComponent& other) = default;
        CurseQbertComponent(CurseQbertComponent&& other) = default;
        CurseQbertComponent& operator=(const CurseQbertComponent& other) = default;
        CurseQbertComponent& operator=(CurseQbertComponent&& other) = default;
        void Update() override;
        void Render() override;
        std::shared_ptr<dae::GameObject> m_Qbert;


    };
}