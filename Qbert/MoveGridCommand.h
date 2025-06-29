#pragma once
#include <glm/glm.hpp>
#include"Command2D.h"
#include<memory>
namespace dae
{
    class GameObject;
  
    class MoveGridCommand : public Command2D
    {
    public:
        MoveGridCommand(std::shared_ptr<dae::GameObject> pGameObject);
        MoveGridCommand();
       virtual void Execute() override;
        
    private:
       
        float deadzone = 0.02f;
        std::shared_ptr<dae::GameObject> m_pGameObject;
        glm::vec3 m_Direction;
        float m_Speed;
        const bool m_UseValue2D = false;

        float tileSize = 48.f;
        float moveSpeed = 40.f;

        int m_PreviousRow = -1;
        int m_PreviousCol = -1;

    };
}

