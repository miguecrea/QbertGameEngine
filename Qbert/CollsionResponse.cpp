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
		/*m_CollidedObjectReference = m_CollisionWithComponent->m_CollideObject;

		if (m_CollidedObjectReference)
		{
			GetComponents();
		}
		m_CollisionWithComponent->m_OnCollisionEvent.Add([this](std::string tag, std::string CollidedObjectTag) {
			OnCollision(tag, CollidedObjectTag);
			}
		);*/

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
	// for player -- Live if live is <= 0 , set scene input names with all the commans controller , i 



	//enemies should die if collides with cube 










	
}
