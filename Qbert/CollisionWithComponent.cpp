#include "CollisionWithComponent.h"
#include "CollisionWithComponent.h"
#include"RectangleComponent.h"
#include"iostream"
#include"GameObject.h"
#include"FreeFallComponent.h"
#include"Audio.h"
#include"staticHeader.h"
#include"TagComponent.h"
#include"CollisionComponent.h"
#include"TimerAndInputComponent.h"
#include"RenderComponent.h"
#include"RotatingCharacterMoveComponent.h"
#include"Renderer.h"
#include"Audio.h"
#include"SceneManager.h"
#include"JumpAnimationComponent.h"
#include"RectangleComponent.h"
#include"EnemyJumpComponent.h"


dae::CollisionWithComponent::CollisionWithComponent(std::vector<std::shared_ptr<GameObject>>& CollideObject) :
	m_CollideObjects{ CollideObject }
{
}

bool::dae::CollisionWithComponent::m_canPlaysound = true;
bool::dae::CollisionWithComponent::m_HasTakenLifeOf = false;
int::dae::CollisionWithComponent::m_SnakePosIndex = 0;

void dae::CollisionWithComponent::BeginPlay()
{
	std::cout << "Collsion With Compoennt Initialized in \n\n";

}

void dae::CollisionWithComponent::Update()
{
	if (!m_canCollide) return;   //remember this 




	SDL_Rect selfRect = this->GetOwner()->GetComponent<dae::RectangleComponent>()->GetRect();

	for (size_t i = 0; i < m_CollideObjects.size(); ++i)
	{
		auto RectComponent = m_CollideObjects[i]->GetComponent<dae::RectangleComponent>();
		SDL_Rect tileRect = m_CollideObjects[i]->GetComponent<dae::RectangleComponent>()->GetRect();
		auto GameObjectsTag = this->GetOwner()->GetComponent<dae::TagComponent>();
		auto CollidingObjectTag = m_CollideObjects[i]->GetComponent<dae::TagComponent>();

		if (!RectComponent->m_Active) continue;

		if (Collides(selfRect, tileRect))
		{
			if (m_CurrentlyCollidingTiles.find(i) == m_CurrentlyCollidingTiles.end())
			{
				//m_CurrentlyCollidingTiles.insert(i); // Mark this tile as "in collision"

				//m_OnCollisionEvent.Broadcast(GameObjectsTag->GetTag(), CollidingObjectTag->GetTag());
				//std::cout << "Collided with tile index: " << i << '\n';


			}

		}
		else
		{
			m_CurrentlyCollidingTiles.erase(i);
		}
	}

}


void dae::CollisionWithComponent::Render()
{

}

void dae::CollisionWithComponent::SetIsAi(bool isAi)
{

	m_IsAi = isAi;
}

void dae::CollisionWithComponent::SetTutorial(bool isTutorial)
{
	m_IsTutorial = isTutorial;
}

bool dae::CollisionWithComponent::Collides(const SDL_Rect& self, const SDL_Rect& objects)
{
	if (self.x + self.w < objects.x || objects.x + objects.w < self.x)
		return false;

	if (self.x > objects.x + objects.w || objects.x > self.x + self.w)
		return false;

	if (self.y + self.h < objects.y || objects.y + objects.h < self.y)
		return false;

	if (self.y > objects.y + objects.h || objects.y > self.y + self.h)
		return false;

	return true;
}

bool dae::CollisionWithComponent::IsAi()
{
	return m_IsAi;
}