#pragma once
#include "Command.h"
#include <glm/glm.hpp>
#include"functional"

namespace dae
{
    class GameObject;
    class SceneManager;

    class UpdatePositionCommand final : public Command
    {
    public:
        UpdatePositionCommand(GameObject * pGameObject, const glm::vec3& direction,int WhoIsTurning);
        void Execute() override;
        void Undo() override;
    private:
        GameObject * m_pGameObject;
        SceneManager * m_pSceneManager{ nullptr };
        glm::vec3 m_OldPosition;
        glm::vec3 m_Direction;
        int m_currentPlayer;


    };
}

