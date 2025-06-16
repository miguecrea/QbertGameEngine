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
dae::CollsionResponse::CollsionResponse()
{
}

void dae::CollsionResponse::BeginPlay()
{
	std::cout << "Collision Response Component Set up\n";

	m_CollisionWithComponent = this->GetOwner()->GetComponent<CollisionWithComponent>();
	
	if (m_CollisionWithComponent)
	{
		m_CollidedObjectReference = m_CollisionWithComponent->m_CollideObject;

		if (m_CollidedObjectReference)
		{
			GetComponents();
		}
		m_CollisionWithComponent->m_OnCollisionEvent.Add([this](std::string tag, std::string CollidedObjectTag) {
			OnCollision(tag, CollidedObjectTag);
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
}

void dae::CollsionResponse::OnCollision(std::string selftag, std::string CollidedObjecTag)
{
	if (selftag == INVISIBLE_RECT)
	{
		HandleInsibleRectCollision(CollidedObjecTag);

		//insible rect called evey time player collides with cube and then collides again
	}
	else if (selftag == BOTTOM_RECT)  
	{
		HandleBottomRectCollision(CollidedObjecTag);

	}
	else if (selftag == PLATFORM)
	{
		HandlePlatformCollision();
	}
	else if (selftag == ROTATING_CHARACTER)
	{
		HandleRotatingCharacterCollision();
	}
}

void dae::CollsionResponse::HandleInsibleRectCollision(std::string CollidedObjecTag)
{
	m_FreFallComponent->SetActive(true);   //activate Object Free Fall

	if (CollidedObjecTag == SNAKE_AI)
	{
		auto EnemyJumpComponent = m_CollidedObjectReference->GetComponent<dae::EnemyJumpComponent>();
	}
	else //diferente a snake 
	{
		if (!m_CollisionComponent->IsFalling())
		{
			dae::SoundSystem& audio{ dae::Audio::Get() };
			audio.Play(s_QbertCurse, 0.5f, 1);
			s_Lives--;
		}
		m_CollisionComponent->SetFallingVariable(true);  //para qure no pueda collisonar los cubos
		m_TimeAndInputComponent->setCanUseInput(false);  //para que no pueda usar input 

	}
}

void dae::CollsionResponse::HandleBottomRectCollision(std::string CollidedObjecTag)
{
	if (m_CollisionWithComponent->IsAi())
	{
		auto EnemyJumpComponent = m_CollidedObjectReference->GetComponent<dae::EnemyJumpComponent>();

		if (EnemyJumpComponent)
		{
		   int ramdom = std::rand() % 3;  // chmager the number in here 
			EnemyJumpComponent->m_TypeOfAi = static_cast<TypeOfAi>(ramdom);
			m_CollidedObjectReference->SetPosition(m_CollidedObjectReference->GetSavedPosition().x, m_CollidedObjectReference->GetSavedPosition().y);
			EnemyJumpComponent->TestFunction();

			return;
		}

	}



	if (!m_CollisionWithComponent->IsAi())
	{
		if (m_FreFallComponent)m_FreFallComponent->SetUnactive();

		if (CollidedObjecTag == SNAKE_AI)
		{
			auto EnemyJumpComponent = m_CollidedObjectReference->GetComponent<dae::EnemyJumpComponent>();

			if (EnemyJumpComponent)
			{
				EnemyJumpComponent->SetActive(true);
				EnemyJumpComponent->Reset();

				int ramdom = std::rand() % 4;
				auto x = EnemyJumpComponent->m_posX[ramdom];   //1 es gg
				auto y = EnemyJumpComponent->m_posY[ramdom];    //3 nopt gg
				m_CollidedObjectReference->SetPosition(x, y);


				if (EnemyJumpComponent->m_TypeOfAi == TypeOfAi::Snake)
				{
					EnemyJumpComponent->m_TypeOfAi = TypeOfAi::SnakeLeft;
				}
				else
				{
					EnemyJumpComponent->m_TypeOfAi = TypeOfAi::Snake;

				}

			}

			auto EnemyRenderComponent = m_CollidedObjectReference->GetComponent<dae::RenderComponent>();

			if (EnemyRenderComponent)
			{
				if (EnemyRenderComponent->m_state == 1)
				{
					EnemyRenderComponent->m_state = 0;
				}
				else
				{
					EnemyRenderComponent->m_state = 1;
				}
			}

		}
		else
		{
			if (m_CollisionComponent) m_CollisionComponent->SetFallingVariable(false);
			if (m_TimeAndInputComponent)	m_TimeAndInputComponent->setCanUseInput(true);

			if (CollidedObjecTag == SNAKE_PLAYER)
			{

				m_CollidedObjectReference->SetPosition(m_CollidedObjectReference->GetSavedPosition().x, m_CollidedObjectReference->GetSavedPosition().y);

			}
			else
			{
				//q bert 

				if (!m_CollisionWithComponent->m_IsTutorial)
				{

					m_CollidedObjectReference->SetPosition(InitialPosX, InitialPosY);

				}
				else
				{
					m_CollidedObjectReference->SetPosition(InitialPosXTutorial, InitialPosYTutorial);

				}
			}

		}
	}

}

void dae::CollsionResponse::HandlePlatformCollision()
{
	this->GetOwner()->GetComponent<dae::RenderComponent>()->SetVisibility(false);
	m_CollidedObjectReference->GetComponent<dae::JumpAnimationComponent>()->Reset();
	m_TimeAndInputComponent->setCanUseInput(false);
	m_CollidedObjectReference->SetPosition(InitialPosX, InitialPosY);
}

void dae::CollsionResponse::HandleRotatingCharacterCollision()
{
	if (Execute)
	{
		std::cout << "Executed first\n";
		Execute = false;
		s_CanUseInput = false;   // be carefullll 
		m_CollidedObjectReference->GetComponent<dae::RenderComponent>()->SetVisibility(false);
		this->GetOwner()->GetComponent<dae::RotatingCharacterMoveComponent>()->m_Active = true;
		this->GetOwner()->GetComponent<dae::RenderComponent>()->SetVisibility(true);
		this->GetOwner()->GetComponent<dae::RectangleComponent>()->SetHeight();
		dae::SoundSystem& audio{ dae::Audio::Get() };
		audio.Play(s_PlatformSound, 0.8f, 1);
	}
	else
	{
		std::cout << "Executed second\n";
		m_OnTimerStarted.Broadcast(m_CollidedObjectReference);

	}
}
