#include "UpdatePositionCommand.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Renderer.h"
#include <iostream>
#include"staticHeader.h"

using namespace dae;

UpdatePositionCommand::UpdatePositionCommand(GameObject * pGameObject, const glm::vec3& direction,int WhoIsTurning)   //pasar 
	: Command{}, m_pGameObject(pGameObject),
	m_OldPosition(pGameObject->GetLocalPosition()),
	m_Direction(direction),
	m_pSceneManager(&SceneManager::GetInstance()),
	m_currentPlayer{WhoIsTurning}

{

}

void UpdatePositionCommand::Execute()
{
	if (!m_pGameObject || s_PauseGame == 1) return;

}

void UpdatePositionCommand::Undo()
{
	if (!m_pGameObject) return;

	m_pGameObject->SetPosition(m_OldPosition.x, m_OldPosition.y);
}


