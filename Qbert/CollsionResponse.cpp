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
	std::cout << "Collision Response Component Set up\n";

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

void dae::CollsionResponse::GetComponents()
{
	m_TagComponent = this->GetOwner()->GetComponent<dae::TagComponent>();
	m_CollidingObjectTagComponent = m_CollidedObjectReference->GetComponent<dae::TagComponent>();
	m_CollisionComponent = m_CollidedObjectReference->GetComponent<dae::CollisionComponent>();
	m_TimeAndInputComponent = m_CollidedObjectReference->GetComponent<dae::TimerAndInputComponent>();
	m_FreFallComponent = m_CollidedObjectReference->GetComponent<dae::FreeFallComponent>();
}



void dae::CollsionResponse::Render()
{
}

void dae::CollsionResponse::Update()
{

	if (m_StartCounter)
	{
		m_CollisionTimer += SceneManager::GetInstance().GetDeltaTime(); 

			if (m_CollisionTimer >= 2.f)
			{
				m_CollisionTimer = 0.f;
				m_StartCounter = false;
				s_PauseEnemy = false;

				//reset variable 

			}

	}
}

void dae::CollsionResponse::OnCollision(std::shared_ptr<dae::GameObject> CollidedObject)
{
	//in a real scale game I can just cast to an interface and executed csutom function for each



	//collison response from enemy class 
	if (auto tagComponent = CollidedObject->GetComponent<TagComponent>())
	{
		if (tagComponent->GetTag() == CUBE)
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
		else if (tagComponent->GetTag() == PENGO)
		{

			m_StartCounter = true;
			s_PauseEnemy = true;
			 
			CollidedObject->SetPosition(48 * 2, 48 * 2);

			auto liveComponent = CollidedObject->GetComponent<dae::LivesComponent>();
			if (liveComponent)
			{
				liveComponent->DecreaseLive();
			}


			std::cout << " Enemy cOLLIDED  Pengo \n";
		}

	}




}
