#include "RotatingCharacterMoveComponent.h"
#include"GameObject.h"
#include"SceneManager.h"
#include"CollsionResponse.h"
#include<iostream>
#include"RenderComponent.h"
#include"staticHeader.h"


dae::RotatingCharacterMoveComponent::RotatingCharacterMoveComponent()
{
}

void dae::RotatingCharacterMoveComponent::BeginPlay()
{
	auto CollisionResponse = GetOwner()->GetComponent<dae::CollsionResponse>();

	if (CollisionResponse)
	{
		CollisionResponse->m_OnTimerStarted.Add([this](std::shared_ptr<dae::GameObject> gameObject)
			{
				OnTimerStarted(gameObject);
			}
		);
	}
}

void dae::RotatingCharacterMoveComponent::Update()
{
	if (m_StartCounter)
	{
		m_CollisionTimer += SceneManager::GetInstance().GetDeltaTime();
	}


	if (m_CollisionTimer >= 1.5f)
	{
		m_CollideObject->GetComponent<dae::RenderComponent>()->SetVisibility(true);
		m_RenderComponent->SetVisibility(false);
		s_CanUseInput = true;
		m_CollisionTimer = 0;
		m_StartCounter = false;

	}

	if (!m_Active) return;
	const float targetX = 93.0f;
	const float targetY = 60.0f;
	glm::vec3 m_OldPosition = GetOwner()->GetLocalPosition();

	glm::vec3 targetPosition(targetX, targetY, 0.0f); // Assuming z-coordinate is 0
	glm::vec3 direction = glm::normalize(targetPosition - m_OldPosition);

	float moveSpeed = 20.f;

	glm::vec3 movement = direction * moveSpeed * SceneManager::GetInstance().GetDeltaTime();

	glm::vec3 newPosition = m_OldPosition + movement;

	GetOwner()->SetPosition(newPosition.x, newPosition.y);
}

void dae::RotatingCharacterMoveComponent::Render()
{
}

void dae::RotatingCharacterMoveComponent::SwapActive()
{
	m_Active = !m_Active;
}

void dae::RotatingCharacterMoveComponent::SetWaitingTime(int waitingTime)
{
	m_WaitingTime = waitingTime;
}

void dae::RotatingCharacterMoveComponent::OnTimerStarted(std::shared_ptr<dae::GameObject> gameObect)
{
	m_StartCounter = true;
	m_CollideObject = gameObect;
	m_RenderComponent = GetOwner()->GetComponent<dae::RenderComponent>();

}
