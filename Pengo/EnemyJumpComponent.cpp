#include "EnemyJumpComponent.h"
#include"GameObject.h"
#include"SceneManager.h"
#include"glm/gtc/constants.hpp."
#include"iostream"
#include"Renderer.h"
#include"Audio.h"
#include"staticHeader.h"




dae::EnemyJumpComponent::EnemyJumpComponent(float jumpWaitingTime, float TimeUntilDrawing, TypeOfAi AiType, float JumpDuration) :
	m_TypeOfAi{ AiType }, m_TimeToUpdate{ jumpWaitingTime }, m_TimeToStartUpdatingObject{ TimeUntilDrawing }, m_Duration{ JumpDuration }
{
	SetSnakeOffsets();
}


void dae::EnemyJumpComponent::Update()
{
	if (!m_Update) return;
	m_pGameObject = GetOwner();
	m_TimeUntilActive += SceneManager::GetInstance().GetDeltaTime();
	if (m_TimeUntilActive >= m_TimeToUpdate)  
	{
		m_TimeUntilActive = 0;
		m_IsActive = true;
		m_execute = true;
	}

	if (!m_IsActive) return;
	if (m_execute)
	{
		m_execute = false;
		m_StartPosition = glm::vec3{ m_pGameObject->GetWorldPosition().x , m_pGameObject->GetWorldPosition().y, 0 };

		m_EndPosition = m_StartPosition + glm::vec3{ m_JumpOffset.x,m_JumpOffset.y, 0 };

	}

	float deltaTime = SceneManager::GetInstance().GetDeltaTime();
	m_Elapsed += deltaTime;

	if (m_Elapsed >= m_Duration)
	{                                      
		m_Elapsed = m_Duration;
		m_IsActive = false;
		m_Elapsed = 0;
		m_StartPosition = m_EndPosition;

		if (m_TypeOfAi == TypeOfAi::RightLeft || m_TypeOfAi == TypeOfAi::LeftRight)
		{
			m_JumpOffset.x = -m_JumpOffset.x;
		}
		if (m_TypeOfAi == TypeOfAi::Snake)
		{
			m_JumpOffset.x = 12;
			m_JumpOffset.y = -m_JumpOffset.y;

		}
		if (m_TypeOfAi == TypeOfAi::SnakeLeft)
		{
			m_JumpOffset.x = -12;
			m_JumpOffset.y = -m_JumpOffset.y;

		}
	}

	float t = m_Elapsed / m_Duration;
	glm::vec3 newPosition = glm::mix(m_StartPosition, m_EndPosition, t);
	newPosition.y += std::sin(t * glm::pi<float>()) * m_ArcHeight; // This is the arc height
	m_pGameObject->SetPosition(newPosition.x, newPosition.y);


}

void dae::EnemyJumpComponent::Render()
{
}

void dae::EnemyJumpComponent::SetActive(bool isActive)
{
	m_Update = isActive;
}

void dae::EnemyJumpComponent::Reset()
{
	m_Elapsed = 0;
}

void dae::EnemyJumpComponent::ChangeSnakeDirection()
{

	m_JumpOffset.x = -m_JumpOffset.x;
}

void dae::EnemyJumpComponent::TestFunction()
{
	std::cout << "Getting called from Enemy Jump\n";
}

void dae::EnemyJumpComponent::SetSnakeOffsets()
{
	switch (m_TypeOfAi)
	{
	case TypeOfAi::RightLeft:
	case TypeOfAi::AllRight:
		m_JumpOffset.x = -m_JumpOffset.x;
		break;

	case TypeOfAi::Snake:
		m_JumpOffset.x = 12;
		m_JumpOffset.y = -20;
		break;

	case TypeOfAi::SnakeLeft:  // right
		m_JumpOffset.x = -12;
		m_JumpOffset.y = -20;
		break;

	default:
		break;
	}

	const float posX[] = { 135.f, 100.f, 126.f, 87.f, 75.f };
	const float posY[] = { 165.f, 148.f, 145.f, 133.f, 145.f };

	for (int i = 0; i < 5; ++i)
	{
		m_posX[i] = posX[i];
		m_posY[i] = posY[i];
	}
}