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

	if (!m_pGameObject) return;
	if (!s_CanUseInput) return;

	auto InputAndTimer = m_pGameObject->GetComponent<dae::TimerAndInputComponent>();
	auto CollisionComponent = m_pGameObject->GetComponent<dae::CollisionComponent>();

	if (CollisionComponent->IsFalling()) return;

	if (InputAndTimer->GetCanUseInput() == false) return;

	InputAndTimer->StartTimer();

	m_renderComponent->m_state = m_QbertState;
	dae::SoundSystem& audio{ dae::Audio::Get() };
	audio.Play(s_QbertJump,m_Volume, 1);

	auto JumpAnimation = m_pGameObject->GetComponent<dae::JumpAnimationComponent>();
	JumpAnimation->SetDirectionInt(m_QbertState);
	JumpAnimation->SetAcive(true);

}

void SetPositionCommand::Undo()
{
	if (!m_pGameObject) return;
	m_pGameObject->SetPosition(m_OldPosition.x, m_OldPosition.y);
}


