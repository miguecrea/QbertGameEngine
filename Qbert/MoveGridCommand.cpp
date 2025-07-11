#include "MoveGridCommand.h"
#include"iostream"
#include"GameObject.h"
#include"SceneManager.h"
#include"RenderComponent.h"
#include"GameObject.h"
#include"PengoComponent.h"
#include"DebugRenderComponent.h"


dae::MoveGridCommand::MoveGridCommand(std::shared_ptr<dae::GameObject> pGameObject, std::shared_ptr<dae::GameObject> map):
	m_Pengo{pGameObject},m_Map{map}

{
	m_RenderComponent = m_Pengo->GetComponent<dae::RenderComponent>();
	m_PengoComponent = m_Pengo->GetComponent<dae::PengoComponent>();

	if (m_Map)
	{
	m_MapComponent = m_Map->GetComponent<dae::MapComponent>();

	}

	//save the map on the scene or in the player 
}

void dae::MoveGridCommand::Execute()
{


	// handle movement event 

	//make sure map is not 



	if (glm::length(m_Value) < deadzone) return;

	if (abs(m_Value.x) > abs(m_Value.y))  // Prioritize horizontal
	{
		m_Direction = { (m_Value.x > 0.f ? 1.f : -1.f), 0.f,0.f};

		RenderingX();

	}
	else 
	{
		m_Direction = { 0.f, (m_Value.y > 0.f ? 1.f : -1.f),0.0f};

		HandleRendering();
	}

	glm::vec3 newPosition = m_Pengo->GetWorldPosition() + m_Direction * SceneManager::GetInstance().GetDeltaTime() * moveSpeed;

	int column = static_cast<int>(std::floor(newPosition.x / tileSize));
	int row = static_cast<int>(std::floor(newPosition.y / tileSize));


	//glm::vec3 snappedPosition{ column * tileSize, row * tileSize, 0.f };

	//std::cout << row << " " << column << "\n";

	//make sure the snapping works 


	//new Position mas with de la sprite s menor todvai esta fuera de la positio n

	// si la posicion de la x +width es todavia adentro 
	if (m_MapComponent->MapArray[row][column] != 9)
	{
	m_Pengo->SetPosition(newPosition.x, newPosition.y);

	}
	

	


	
	

	
	//get needs the map game object as well as parameters 

	//first make  it move left right ,up and down
	// //save the direction it is looking at 
	// snap to grid 
	// make sure it wont hit anything all rhe other blocks 
	// 
	//then we 

	//when we hit a block game object broadcast commands //and maps uddates etc 
	//hit and break block



}

void dae::MoveGridCommand::RenderingX()
{
	if (m_Direction.x == 1.f)
	{
		if (m_RenderComponent && m_PengoComponent)
		{
			m_RenderComponent->m_state = 3;
			m_PengoComponent->m_CurrentDirection = Direction::RIGHT;

		}
	}
	else
	{
		if (m_RenderComponent)
		{
			m_RenderComponent->m_state = 1;
			m_PengoComponent->m_CurrentDirection = Direction::LEFT;

		}

	}
}

void dae::MoveGridCommand::HandleRendering()
{
	if (m_Direction.y == 1.f)
	{
		if (m_RenderComponent)
		{
			m_RenderComponent->m_state = 0;
			m_PengoComponent->m_CurrentDirection = Direction::DOWN;

		}
	}
	else
	{
		if (m_RenderComponent)
		{
			m_RenderComponent->m_state = 2;
			m_PengoComponent->m_CurrentDirection = Direction::UP;

		}

	}
}
