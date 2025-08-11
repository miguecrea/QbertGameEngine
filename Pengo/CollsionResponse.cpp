#include "CollsionResponse.h"
#include"CollisionWithComponent.h"
#include"iostream"
#include"CollisionComponent.h"
#include"TagComponent.h"
#include"FreeFallComponent.h"
#include"CollisionComponent.h"
#include"TimerAndInputComponent.h"
#include"EnemyJumpComponent.h"
#include"Audio.h"
#include"staticHeader.h"
#include"RenderComponent.h"
#include"JumpAnimationComponent.h"
#include"RotatingCharacterMoveComponent.h"
#include"RectangleComponent.h"
#include"SceneManager.h"
#include"Tags.h"
#include"LivesComponent.h"
#include"AiComponent.h"
#include"EnemySpawner.h"

dae::CollsionResponse::CollsionResponse()
{
}

void dae::CollsionResponse::BeginPlay()
{

	GetComponentsAndDelegate();
}

void dae::CollsionResponse::GetComponentsAndDelegate()
{
	m_CollisionWithComponent = this->GetOwner()->GetComponent<CollisionWithComponent>();
	m_AiComponent = this->GetOwner()->GetComponent<AIComponent>();
	m_RenderComponent = this->GetOwner()->GetComponent<RenderComponent>();

	if (m_CollisionWithComponent)
	{
		m_CollisionWithComponent->m_OnCollisionEvent.Add([this](std::shared_ptr<dae::GameObject> CollidedObject)
			{
				OnCollision(CollidedObject);
			}
		);

	}
}




void dae::CollsionResponse::Render()
{
}

void dae::CollsionResponse::Update()
{

	HandleEnemyPauseBehavior();
}

void dae::CollsionResponse::HandleEnemyPauseBehavior()
{
	if (m_StartCounter)
	{
		m_CollisionTimer += SceneManager::GetInstance().GetDeltaTime();

		if (m_CollisionTimer >= m_TimeUntilUnpausing)
		{
			m_CollisionTimer = 0.f;
			m_StartCounter = false;
			s_PauseEnemy = false;
		}
	}
}

void dae::CollsionResponse::OnCollision(std::shared_ptr<dae::GameObject> CollidedObject)
{

	if (auto tagComponent = CollidedObject->GetComponent<TagComponent>())
	{
		if (tagComponent->GetTag() == CUBE)
		{
			OnEnemyKilled();

		}
		else if (tagComponent->GetTag() == PENGO)
		{
			OnPlayerDead(CollidedObject);
		}

	}

}

void dae::CollsionResponse::OnEnemyKilled()
{
	if (m_CollisionWithComponent)
	{
		m_CollisionWithComponent->m_canCollide = false;

	}
	if (m_AiComponent)
	{
		m_AiComponent->m_dead = true;
	}

	if (m_RenderComponent)
	{
		m_RenderComponent->SetVisibility(false);
	}

	if (m_EnemySpawner)
	{
		m_EnemySpawner->DecreaseEnemyCount();
	}


	dae::SoundSystem& audio{ dae::Audio::Get() };
	audio.Play(S_EnemyDead, 0.5f, 0);
}

void dae::CollsionResponse::OnPlayerDead(std::shared_ptr<dae::GameObject>& CollidedObject)
{
	m_StartCounter = true;
	s_PauseEnemy = true;

	CollidedObject->SetPosition(48 * 2, 48 * 2);

	auto liveComponent = CollidedObject->GetComponent<dae::LivesComponent>();
	if (liveComponent)
	{
		liveComponent->DecreaseLive();
	}

}
