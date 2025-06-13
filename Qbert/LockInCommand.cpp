#include "LockInCommand.h"
#include"GameObject.h"
#include"KeyBoardComponent.h"
#include"iostream"
#include"staticHeader.h"
#include"Audio.h"


dae::LockInCommand::LockInCommand(std::vector<std::shared_ptr<dae::GameObject>>& obejcts) :
	m_objects{ obejcts }
{
}

void dae::LockInCommand::Execute()
{
	int Activeindex = m_objects[0]->GetComponent<dae::KeyBoardComponent>()->m_ActiveIndex;
	char key = m_objects[Activeindex]->GetComponent<dae::KeyBoardComponent>()->m_key;
	std::cout << key << " ";

	if (Activeindex == m_objects.size() - 1)
	{
		if (!s_PlayerName.empty())
		{
			s_PlayerName.pop_back(); 
		}
	}
	else
	{
		s_PlayerName += key;
	}
	dae::SoundSystem& audio{ dae::Audio::Get() };
	audio.Play(s_KeyBoardkeyMusic, 0.5f, 1);
}

void dae::LockInCommand::Undo()
{
}
