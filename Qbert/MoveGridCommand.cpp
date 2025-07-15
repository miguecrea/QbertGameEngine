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

	CollisionWithTiles();
	
}

void dae::MoveGridCommand::CollisionWithTiles()
{
	glm::vec3 newPosition = m_Pengo->GetWorldPosition() + m_Direction * SceneManager::GetInstance().GetDeltaTime() * moveSpeed;

	glm::vec3 Pos2{ m_Pengo->GetWorldPosition().x + m_CharacterWidth,m_Pengo->GetWorldPosition().y,0 };
	glm::vec3 Pos3{ m_Pengo->GetWorldPosition().x,m_Pengo->GetWorldPosition().y + m_CharacterWidth,0 };
	glm::vec3 Pos4{ m_Pengo->GetWorldPosition().x + m_CharacterWidth,m_Pengo->GetWorldPosition().y + m_CharacterWidth,0 };


	glm::vec3 newPosition2 = Pos2 + m_Direction * SceneManager::GetInstance().GetDeltaTime() * moveSpeed;
	glm::vec3 newPosition3 = Pos3 + m_Direction * SceneManager::GetInstance().GetDeltaTime() * moveSpeed;
	glm::vec3 newPosition4 = Pos4 + m_Direction * SceneManager::GetInstance().GetDeltaTime() * moveSpeed;

	int column = static_cast<int>(std::floor(newPosition.x / tileSize));
	int row = static_cast<int>(std::floor(newPosition.y / tileSize));

	int columnTopRight = static_cast<int>(std::floor(newPosition2.x / tileSize));
	int rowTopRight = static_cast<int>(std::floor(newPosition2.y / tileSize));

	int columnBottomLeft = static_cast<int>(std::floor(newPosition3.x / tileSize));
	int rowBottomLeft = static_cast<int>(std::floor(newPosition3.y / tileSize));

	int columnBottomRight = static_cast<int>(std::floor(newPosition4.x / tileSize));
	int rowBottomRight = static_cast<int>(std::floor(newPosition4.y / tileSize));

	if (!Collides(row, column) && !Collides(rowTopRight, columnTopRight) && !Collides(rowBottomRight, columnBottomLeft) && !Collides(rowBottomLeft, columnBottomRight))
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

bool dae::MoveGridCommand::Collides(int row, int columns)
{
	
	if (m_MapComponent->MapArray[row][columns] != 9 && m_MapComponent->MapArray[row][columns] != 8 && m_MapComponent->MapArray[row][columns] != 5)
	{
		return false;
	}

	return true;
}
