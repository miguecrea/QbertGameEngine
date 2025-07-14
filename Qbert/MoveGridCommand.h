#pragma once
#include <glm/glm.hpp>
#include"Command2D.h"
#include<memory>
#include"PengoDirection.h"
namespace dae
{
    class GameObject;
    class RenderComponent;
    class PengoComponent;
    class MapComponent;
  
    class MoveGridCommand : public Command2D
    {
    public:
        MoveGridCommand(std::shared_ptr<dae::GameObject> pGameObject, std::shared_ptr<dae::GameObject> map,Direction Pengodirec = Direction::DOWN,bool usekeybaord = false);
       virtual void Execute() override;

       void RenderingX();

       void HandleRendering();
        
    private:
       
        float deadzone = 0.2f;
        std::shared_ptr<dae::GameObject> m_Pengo;
        std::shared_ptr<dae::GameObject> m_Map;
        std::shared_ptr<dae::RenderComponent> m_RenderComponent;
        std::shared_ptr<dae::PengoComponent> m_PengoComponent;
        Direction m_PengoDirection;
        bool m_usekeyboard = false;

        std::shared_ptr<dae::MapComponent> m_MapComponent;
        glm::vec3 m_Direction;
        float m_Speed;
        const bool m_UseValue2D = false;

        float tileSize = 48.f;
        float moveSpeed = 80.f;

        int m_PreviousRow = -1;
        int m_PreviousCol = -1;
        float Timer = 0.f;

    };
}

