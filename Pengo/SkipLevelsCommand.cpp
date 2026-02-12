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
#include"BreakMoveTileCommand.h"
#include"MoveGridCommand.h"
#include<memory>
#include"PengoDirection.h"

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

	auto scene = SceneManager::GetInstance().GetCurrentScene();
	ClearInputBindings(input, scene);
}

void dae::SkipLevelsCommand::ClearInputBindings(dae::InputManager& input,Scene * scene)
{
	//auto newScene = SceneManager::GetInstance().GetCurrentScene();

	input.ClearSpecificControllerAndKeyboard();
	input.m_ShouldClearController = true;

	auto keyboard = input.GetKeyboard();

	keyboard->MapCommandToButton(SDL_SCANCODE_W, std::make_unique<dae::MoveGridCommand>(scene->m_player, scene->m_Map, Direction::UP, true), dae::ButtonState::Pressed);
	keyboard->MapCommandToButton(SDL_SCANCODE_A, std::make_unique<dae::MoveGridCommand>(scene->m_player, scene->m_Map, Direction::LEFT, true), dae::ButtonState::Pressed);
	keyboard->MapCommandToButton(SDL_SCANCODE_S, std::make_unique<dae::MoveGridCommand>(scene->m_player, scene->m_Map, Direction::DOWN, true), dae::ButtonState::Pressed);
	keyboard->MapCommandToButton(SDL_SCANCODE_D, std::make_unique<dae::MoveGridCommand>(scene->m_player, scene->m_Map, Direction::RIGHT, true), dae::ButtonState::Pressed);
	keyboard->MapCommandToButton(SDL_SCANCODE_K, std::make_unique<dae::BreakMoveTileCommand>(scene->m_player), dae::ButtonState::Up);

	input.m_PostClearCallback = [=]()
		{
			auto controller = InputManager::GetInstance().AddController();
			controller->MapCommandToThumbstick(dae::Controller::ControllerThumbsticks::LeftThumbstick, std::make_unique<dae::MoveGridCommand>(scene->m_player, scene->m_Map));
			controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonA, std::make_unique<dae::BreakMoveTileCommand>(scene->m_player), dae::ButtonState::Up);
		};

	dae::SoundSystem& audio{ dae::Audio::Get() };
	audio.Play(s_MenuMusicId, 0.5f,100);
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
