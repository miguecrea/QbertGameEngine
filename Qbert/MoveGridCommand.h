#pragma once
#include <glm/glm.hpp>
#include"Command2D.h"

namespace dae
{
    class GameObject;
  
    class MoveGridCommand : public Command2D
    {
    public:
        MoveGridCommand(GameObject * pGameObject, const glm::vec2 &  direction, bool useValue2D = false);
       virtual void Execute() override;
        
    private:
       
        glm::vec2 m_Direction;
        float m_Speed;
        const bool m_UseValue2D = false;
    };
}

