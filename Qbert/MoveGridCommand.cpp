#include "MoveGridCommand.h"
#include"iostream"
#include"GameObject.h"
#include"SceneManager.h"
#include"RenderComponent.h"
#include"GameObject.h"
#include"PengoComponent.h"
#include"DebugRenderComponent.h"


dae::MoveGridCommand::MoveGridCommand(std::shared_ptr<dae::GameObject> pGameObject, std::shared_ptr<dae::GameObject> map, Direction Pengodirec,bool usekeybaord):
	m_Pengo{pGameObject},m_Map{map},m_PengoDirection{ Pengodirec},m_usekeyboard{usekeybaord}

{
	m_RenderComponent = m_Pengo->GetComponent<dae::RenderComponent>();
	m_PengoComponent = m_Pengo->GetComponent<dae::PengoComponent>();

	if (m_Map)
	{
	m_MapComponent = m_Map->GetComponent<dae::MapComponent>();

	}

}


void dae::MoveGridCommand::Execute()
{



	if (m_usekeyboard)
	{
		switch (m_PengoDirection)
		{
		case Direction::UP:

			m_Direction = glm::vec3(0.f, -1.f,0);
			m_RenderComponent->m_state = 2;
			m_PengoComponent->m_CurrentDirection = Direction::UP;
			break;
		case Direction::DOWN:
			m_Direction = glm::vec3(0.f, 1.f,0);
			m_RenderComponent->m_state = 0;
			m_PengoComponent->m_CurrentDirection = Direction::DOWN;

			break;
		case Direction::LEFT:
			m_Direction = glm::vec3(-1.f, 0.f,0);
			m_RenderComponent->m_state = 1;
			m_PengoComponent->m_CurrentDirection = Direction::LEFT;


			break;
		case Direction::RIGHT:
			m_Direction = glm::vec3(1.f, 0.f,0);
			m_RenderComponent->m_state = 3;
			m_PengoComponent->m_CurrentDirection = Direction::RIGHT;


			break;
		default:
			break;
		}
	}
	else
	{
		if (glm::length(m_Value) < deadzone) return;

		if (abs(m_Value.x) > abs(m_Value.y))  // Prioritize horizontal
		{
			m_Direction = { (m_Value.x > 0.f ? 1.f : -1.f), 0.f,0.f };

			RenderingX();

		}
		else
		{
			m_Direction = { 0.f, (m_Value.y > 0.f ? 1.f : -1.f),0.0f };

			HandleRendering();
		}

	}


	glm::vec3 newPosition = m_Pengo->GetWorldPosition() + m_Direction * SceneManager::GetInstance().GetDeltaTime() * moveSpeed;

	int column = static_cast<int>(std::floor(newPosition.x / tileSize));
	int row = static_cast<int>(std::floor(newPosition.y/ tileSize));

	if (m_MapComponent->MapArray[row][column] != 9 && m_MapComponent->MapArray[row][column] != 8 && m_MapComponent->MapArray[row][column] != 5)
	{
	m_Pengo->SetPosition(newPosition.x, newPosition.y);

	}
	



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
