#include "SkipLevelsCommand.h"
#include"SceneManager.h"
#include"iostream"
#include"Scene.h"
#include"AddInput.h"
#include"InputManager.h"
#include<memory.h>
#include"Audio.h"
#include"staticHeader.h"
#include"Tags.h"

dae::SkipLevelsCommand::SkipLevelsCommand()
{
}

int dae::SkipLevelsCommand::m_index = 1;

void dae::SkipLevelsCommand::Execute()
{
	auto& input = InputManager::GetInstance();
	auto OldScene = SceneManager::GetInstance().GetCurrentScene();

	if (OldScene->GetId() == 0) return;

	if (m_index == MAX_NUMBER_SCENES)
	{
		m_index = 0;
	}

	m_index++;
	ChooseScene();
	ClearInputBindings(input);
}

void dae::SkipLevelsCommand::ClearInputBindings(dae::InputManager& input)
{
	//auto newScene = SceneManager::GetInstance().GetCurrentScene();
	//input.ClearSpecificControllerAndKeyboard();
	//auto render = newScene->m_player->GetComponent<dae::RenderComponent>();
	//AddControllerKeyboardPlayer1(newScene->m_player, render);
	//dae::SoundSystem& audio{ dae::Audio::Get() };
	//audio.Play(s_GameSoundId, 0.5f, 1);

	////add keybard ad mouse 



}

void dae::SkipLevelsCommand::ChooseScene()
{
	switch (m_index)
	{
	case 1:

		SceneManager::GetInstance().SetCurrentScene(SINGLE_PLAYER_SCENE);
		break;
	case 2:
		SceneManager::GetInstance().SetCurrentScene(LEVEL_2);
		break;

	case 3:
		SceneManager::GetInstance().SetCurrentScene(LEVEL_3);

		break;
	default:
		SceneManager::GetInstance().SetCurrentScene(LEVEL_3);
		break;
	}
}

void dae::SkipLevelsCommand::Undo()
{
	m_index++;
}

void dae::SkipLevelsCommand::AddToIndex()
{
}
