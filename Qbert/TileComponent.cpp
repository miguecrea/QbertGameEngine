#include "TileComponent.h"
#include"TileStaticHelper.h"
#include"GameObject.h"
#include"iostream"
#include"SceneManager.h"
#include"RenderComponent.h"
#include"RectangleComponent.h"
#include"DebugRenderComponent.h"
#include"Audio.h"
#include <random>
#include <cmath>
#include"staticHeader.h"

dae::TileComponent::TileComponent()
{
	m_SecondsUntilSpawning = RandomFloatStep1(m_MinSeconds, m_MaxSeconds);
}

void dae::TileComponent::SetActive(Direction direction)
{
	m_Direction = direction;
	m_StartMoving = true;

}

void dae::TileComponent::SetMap(MapComponent * Map)
{
	m_Map = Map;
}

void dae::TileComponent::BeginPlay()
{
	m_renderComponent = GetOwner()->GetComponent<dae::RenderComponent>();
	m_RectangleComponent = GetOwner()->GetComponent<dae::RectangleComponent>();

	

}

void dae::TileComponent::Render()
{

	//Renderer::GetInstance().DrawSquare(this->GetOwner()->GetWorldPosition().x, this->GetOwner()->GetWorldPosition().y,30.f, SDL_Color{ 255,255,255,250 });

}

void dae::TileComponent::Update()
{

	
	//event called spawn enemy 



	//what id I destroy it before thjis reaches the end 
    //make a bool destroyed 
	if (m_IsNest)
	{
		m_Timer += SceneManager::GetInstance().GetDeltaTime();

		if (m_Timer >= m_SecondsUntilSpawning && !m_Destroyed)
		{


			m_Timer = 0;
			m_IsNest = false;

			if (!m_StartMoving)
			{
			m_Map->m_TileObjects[m_CurrentRow, m_CurrentColumn]->reset();
			m_Map->MapArray[m_CurrentRow][m_CurrentColumn] = 0;

			}
			else
			{
				m_Map->m_TileObjects[m_DesiredRow, m_DesiredColumn]->reset();
				m_Map->MapArray[m_DesiredRow][m_DesiredRow] = 0;

			}

			m_renderComponent->SwapVisibility();
			m_BlockHatched.Broadcast(GetOwner()->GetWorldPosition().x, GetOwner()->GetWorldPosition().y);

			std::cout << "Finito\n";
			dae::SoundSystem& audio{ dae::Audio::Get() };
			audio.Play(s_EnemySpawned, 0.5f, 0);


		}

		//starts counter if counter feels reset map and /array of tiles 
		//and also set render to false 

	}





	float x = this->GetOwner()->GetWorldPosition().x + m_TileSize / 2;
	float y = this->GetOwner()->GetWorldPosition().y + m_TileSize / 2;

	float targetX = m_DesiredColumn * m_TileSize + (m_TileSize / 2);
	float targetY = m_DesiredRow * m_TileSize + (m_TileSize / 2);

	float epsilon = 1.f; 

	if (std::abs(y - targetY) <= epsilon  && std::abs(x - targetX) <= epsilon)
	{
		m_StartMoving = false;
		
		m_CurrentRow = m_DesiredRow;
		m_CurrentColumn = m_DesiredColumn;
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

float dae::TileComponent::RandomFloatStep1(float min, float max)
{
	

	if (min > max) std::swap(min, max);

	int minInt = static_cast<int>(std::ceil(min));
	int maxInt = static_cast<int>(std::floor(max));

	if (minInt > maxInt) return minInt * 1.0f; // no valid integer step in range

	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(minInt, maxInt);

	return static_cast<float>(dist(gen));
}
