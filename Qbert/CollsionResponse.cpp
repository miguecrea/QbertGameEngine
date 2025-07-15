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

dae::CollsionResponse::CollsionResponse()
{
}

void dae::CollsionResponse::BeginPlay()
{
	std::cout << "Collision Response Component Set up\n";

	m_CollisionWithComponent = this->GetOwner()->GetComponent<CollisionWithComponent>();
	
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
}

void dae::CollsionResponse::OnCollision(std::shared_ptr<dae::GameObject> CollidedObject)
{
	//in a real scale game I can just cast to an interface and executed csutom function for each


	if (auto tagComponent = CollidedObject->GetComponent<TagComponent>())
	{
		if (tagComponent->GetTag() == CUBE)
		{

		   std::cout << " Enemy cOLLIDED  tile \n";

			
		}
		else if (tagComponent->GetTag() == PENGO)
		{
			auto liveComponent = CollidedObject->GetComponent<dae::LivesComponent>();
			if (liveComponent)
			{
				liveComponent->DecreaseLive();
			}
		std::cout << " Enemy cOLLIDED  Pengo \n";
		}

	}


	if (CollidedObject)
	{
	}

	//std::cout << " Enemy Died\n";
	// for player -- Live if live is <= 0 , set scene input names with all the commans controller , i 
	//enemies should die if collides with cube 


	
}
