#include "MoveGridCommand.h"
#include"iostream"
#include"GameObject.h"
#include"SceneManager.h"
#include"RenderComponent.h"
#include"GameObject.h"


dae::MoveGridCommand::MoveGridCommand(std::shared_ptr<dae::GameObject> pGameObject):
	m_pGameObject{pGameObject}

{
	m_RenderComponent = m_pGameObject->GetComponent<dae::RenderComponent>();
}

dae::MoveGridCommand::MoveGridCommand()
{
}

void dae::MoveGridCommand::Execute()
{


	// handle movement event 



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

	glm::vec3 newPosition = m_pGameObject->GetWorldPosition() + m_Direction * SceneManager::GetInstance().GetDeltaTime() * moveSpeed;

	int column = static_cast<int>(std::floor(newPosition.x / tileSize));
	int row = static_cast<int>(std::floor(newPosition.y / tileSize));


	glm::vec3 snappedPosition{ column * tileSize, row * tileSize, 0.f };

	std::cout << row << " " << column << "\n";

	
	m_pGameObject->SetPosition(snappedPosition.x, snappedPosition.y);

	


	
	

	
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
		if (m_RenderComponent)
		{
			m_RenderComponent->m_state = 3;

		}
	}
	else
	{
		if (m_RenderComponent)
		{
			m_RenderComponent->m_state = 1;
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

		}
	}
	else
	{
		if (m_RenderComponent)
		{
			m_RenderComponent->m_state = 2;
		}

	}
}
