#include "SetPositionCommand.h"
#include "GameObject.h"
#include"SceneManager.h"
#include"RenderComponent.h"
#include"JumpAnimationComponent.h"
#include"Audio.h"
#include"staticHeader.h"
#include"TimerAndInputComponent.h"
#include"CollisionComponent.h"

using namespace dae;

SetPositionCommand::SetPositionCommand(GameObject *  pGameObject, const glm::vec3& direction, std::shared_ptr<dae::RenderComponent> renderComponent, int Direction)
	: Command{}, m_pGameObject(pGameObject), m_OldPosition(pGameObject->GetLocalPosition()), m_Direction(direction), m_renderComponent{ renderComponent }, m_QbertState{ Direction }
	, m_JumpAnimation{ nullptr }
{

};

void SetPositionCommand::Execute()
{



}

void SetPositionCommand::Undo()
{
	if (!m_pGameObject) return;
	m_pGameObject->SetPosition(m_OldPosition.x, m_OldPosition.y);
}


