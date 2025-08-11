#include "ChangeSelectionCommand.h"
#include"GameObject.h"
#include"KeyBoardComponent.h"
#include"iostream"
#include"staticHeader.h"


dae::ChangeSelectionCommand::ChangeSelectionCommand(std::vector<std::shared_ptr<GameObject>>& obejcts, int currentActiveTile, Direction keyDirection) :
	m_currentActiveTile{ currentActiveTile }, m_objects{ obejcts }, m_KeyDirection{ keyDirection }
{
}

void dae::ChangeSelectionCommand::Execute()
{




	GetCharacterBasedOnDirection();

	auto compo = m_objects[s_CurrentCharacter]->GetComponent<dae::KeyBoardComponent>();
	compo->m_IsActive = true;
	for (int i = 0; i < m_objects.size(); i++)
	{
		m_objects[i]->GetComponent<dae::KeyBoardComponent>()->m_ActiveIndex = s_CurrentCharacter;
		if (i == s_CurrentCharacter) continue;
		m_objects[i]->GetComponent<dae::KeyBoardComponent>()->m_IsActive = false;
	}
}

void dae::ChangeSelectionCommand::GetCharacterBasedOnDirection()
{
	int col = s_CurrentCharacter % COLUMNS;
	int row = s_CurrentCharacter / COLUMNS;

	switch (m_KeyDirection)
	{
	case Direction::LEFT:

		if (col > 0)
		{
			s_CurrentCharacter--;
		}
		break;

	case Direction::RIGHT:

		if (col < COLUMNS - 1)
		{
			s_CurrentCharacter++;
		}
		break;

	case Direction::UP:

		if (row > 0)
		{
			s_CurrentCharacter -= COLUMNS;
		}

		break;
	case Direction::DOWN:

		if (row < ROWS - 1)
		{
			s_CurrentCharacter += COLUMNS;

		}
		break;
	default:
		break;
	}
}

void dae::ChangeSelectionCommand::Undo()
{
}

int dae::ChangeSelectionCommand::Clamp(int number, int min, int max)
{

	if (number > min && number < max)
	{
		return number;
	}
	if (number >= max)
	{
		return max;
	}
	if (number <= max)
	{
		return min;
	}

	return number;
}
