#include "TileComponent.h"
#include"TileStaticHelper.h"
#include"GameObject.h"
#include"iostream"
#include"SceneManager.h"
#include"RenderComponent.h"
#include"RectangleComponent.h"

dae::TileComponent::TileComponent()
{
}

void dae::TileComponent::SetActive(Direction direction)
{
	m_Direction = direction;
	m_StartMoving = true;

}

void dae::TileComponent::BeginPlay()
{


	m_renderComponent = GetOwner()->GetComponent<dae::RenderComponent>();
	m_RectangleComponent = GetOwner()->GetComponent<dae::RectangleComponent>();


	//get render component and add hakf width and height to it 

}

void dae::TileComponent::Render()
{

	//Renderer::GetInstance().DrawSquare(this->GetOwner()->GetWorldPosition().x, this->GetOwner()->GetWorldPosition().y,30.f, SDL_Color{ 255,255,255,250 });

}

void dae::TileComponent::Update()
{
	float x = this->GetOwner()->GetWorldPosition().x + m_TileSize / 2;
	float y = this->GetOwner()->GetWorldPosition().y + m_TileSize / 2;

	float targetX = m_DesiredColumn * m_TileSize + (m_TileSize / 2);
	float targetY = m_DesiredRow * m_TileSize + (m_TileSize / 2);

	float epsilon = 1.f; 

	if (std::abs(y - targetY) <= epsilon  && std::abs(x - targetX) <= epsilon)
	{
		m_StartMoving = false;
		
		if (m_RectangleComponent)
		{
		m_RectangleComponent->m_Active = false;

		}

	}
	if (m_StartMoving)
	{
		glm::vec3 DirectionVector{};

		switch (m_Direction)
		{
		case Direction::UP:
			DirectionVector = glm::vec3(0.0f,-1.f, 0);
			break;
		case Direction::DOWN:
			DirectionVector = glm::vec3(0.0f, 1.f, 0);
			break;
		case Direction::LEFT:
			DirectionVector = glm::vec3(-1.0f, 0.f, 0);
			break;
		case Direction::RIGHT:
			DirectionVector = glm::vec3(1.0f, 0.f, 0);
			break;
		default:
			break;
		}
		
		glm::vec3 newPosition = this->GetOwner()->GetWorldPosition() + DirectionVector * SceneManager::GetInstance().GetDeltaTime() * m_MovementSpeed;
		this->GetOwner()->SetPosition(newPosition.x, newPosition.y);
	}
}
