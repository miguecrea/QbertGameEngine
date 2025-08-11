#include "OpenLevelCommand.h"
#include"ChangeModeCommand.h"
#include"GameObject.h"
#include"SaveLevelComponent.h"
#include"SceneManager.h"
#include"iostream"
#include"Audio.h"
#include"staticHeader.h"
#include"InputManager.h"
#include"Scene.h"
#include"MoveGridCommand.h"
#include"BreakMoveTileCommand.h"
#include"Tags.h"
#include"PengoDirection.h"
#include"LockInCommand.h"
#include"ChangeSelectionCommand.h"

dae::OpenLevelCommand::OpenLevelCommand(std::vector<std::shared_ptr<dae::GameObject>> TextGameObjects, ChangeModeCommand* command) :
	m_TextGameObjects{ TextGameObjects }, m_ChangeModeCommand{ command }
{
}

void dae::OpenLevelCommand::Execute()
{

	if (!m_ChangeModeCommand) return;


	int CurrentIndex = m_ChangeModeCommand->GetCurrentIndex();
	auto SaveLevelComppnent = m_TextGameObjects[CurrentIndex]->GetComponent<dae::SaveLevelComponent>();

	if (SaveLevelComppnent)
	{
		SceneManager::GetInstance().SetCurrentScene(SaveLevelComppnent->GetLevelName());

		auto scene = SceneManager::GetInstance().GetCurrentScene();

		auto& input = dae::InputManager::GetInstance();
		input.ClearSpecificControllerAndKeyboard();
		input.m_ShouldClearController = true;


		auto keyboard{ input.GetKeyboard() };   //second uses keyboard 



		if (SaveLevelComppnent->GetLevelName() == SINGLE_PLAYER_SCENE)  // o si es level idk if level 2 maybe in the other with keybaord
		{

			AddKeyBindOnePerson(keyboard, scene, input);


		}
		else if (SaveLevelComppnent->GetLevelName() == CO_OP_SCENE)
		{

			s_Lives = 6;

			keyboard->MapCommandToButton(SDL_SCANCODE_W, std::make_unique<dae::MoveGridCommand>(scene->m_player, scene->m_Map, Direction::UP, true), dae::ButtonState::Pressed);
			keyboard->MapCommandToButton(SDL_SCANCODE_A, std::make_unique<dae::MoveGridCommand>(scene->m_player, scene->m_Map, Direction::LEFT, true), dae::ButtonState::Pressed);
			keyboard->MapCommandToButton(SDL_SCANCODE_S, std::make_unique<dae::MoveGridCommand>(scene->m_player, scene->m_Map, Direction::DOWN, true), dae::ButtonState::Pressed);
			keyboard->MapCommandToButton(SDL_SCANCODE_D, std::make_unique<dae::MoveGridCommand>(scene->m_player, scene->m_Map, Direction::RIGHT, true), dae::ButtonState::Pressed);
			keyboard->MapCommandToButton(SDL_SCANCODE_K, std::make_unique<dae::BreakMoveTileCommand>(scene->m_player), dae::ButtonState::Up);


			keyboard->MapCommandToButton(SDL_SCANCODE_T, std::make_unique<dae::MoveGridCommand>(scene->m_player2, scene->m_Map, Direction::UP, true), dae::ButtonState::Pressed);
			keyboard->MapCommandToButton(SDL_SCANCODE_F, std::make_unique<dae::MoveGridCommand>(scene->m_player2, scene->m_Map, Direction::LEFT, true), dae::ButtonState::Pressed);
			keyboard->MapCommandToButton(SDL_SCANCODE_G, std::make_unique<dae::MoveGridCommand>(scene->m_player2, scene->m_Map, Direction::DOWN, true), dae::ButtonState::Pressed);
			keyboard->MapCommandToButton(SDL_SCANCODE_H, std::make_unique<dae::MoveGridCommand>(scene->m_player2, scene->m_Map, Direction::RIGHT, true), dae::ButtonState::Pressed);
			keyboard->MapCommandToButton(SDL_SCANCODE_U, std::make_unique<dae::BreakMoveTileCommand>(scene->m_player2), dae::ButtonState::Up);


			input.m_PostClearCallback = [=]()
				{
					auto controller = InputManager::GetInstance().AddController();

					controller->MapCommandToThumbstick(dae::Controller::ControllerThumbsticks::LeftThumbstick, std::make_unique<dae::MoveGridCommand>(scene->m_player, scene->m_Map));
					controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonA, std::make_unique<dae::BreakMoveTileCommand>(scene->m_player), dae::ButtonState::Up);


					auto controller2 = InputManager::GetInstance().AddController();
					controller2->MapCommandToThumbstick(dae::Controller::ControllerThumbsticks::LeftThumbstick, std::make_unique<dae::MoveGridCommand>(scene->m_player2,scene->m_Map));
					controller2->MapCommandToButton(dae::Controller::ControllerButtons::ButtonA, std::make_unique<dae::BreakMoveTileCommand>(scene->m_player2), dae::ButtonState::Up);
				};


		
			dae::SoundSystem& audio{ dae::Audio::Get() };
			audio.Play(s_MenuMusicId, 0.2f, 100);



		}
		else if (SaveLevelComppnent->GetLevelName() == VERSUS_MODE)
		{


			keyboard->MapCommandToButton(SDL_SCANCODE_W, std::make_unique<dae::MoveGridCommand>(scene->m_player, scene->m_Map, Direction::UP, true), dae::ButtonState::Pressed);
			keyboard->MapCommandToButton(SDL_SCANCODE_A, std::make_unique<dae::MoveGridCommand>(scene->m_player, scene->m_Map, Direction::LEFT, true), dae::ButtonState::Pressed);
			keyboard->MapCommandToButton(SDL_SCANCODE_S, std::make_unique<dae::MoveGridCommand>(scene->m_player, scene->m_Map, Direction::DOWN, true), dae::ButtonState::Pressed);
			keyboard->MapCommandToButton(SDL_SCANCODE_D, std::make_unique<dae::MoveGridCommand>(scene->m_player, scene->m_Map, Direction::RIGHT, true), dae::ButtonState::Pressed);
			keyboard->MapCommandToButton(SDL_SCANCODE_K, std::make_unique<dae::BreakMoveTileCommand>(scene->m_player), dae::ButtonState::Up);


			keyboard->MapCommandToButton(SDL_SCANCODE_T, std::make_unique<dae::MoveGridCommand>(scene->m_enemy, scene->m_Map, Direction::UP, true), dae::ButtonState::Pressed);
			keyboard->MapCommandToButton(SDL_SCANCODE_F, std::make_unique<dae::MoveGridCommand>(scene->m_enemy, scene->m_Map, Direction::LEFT, true), dae::ButtonState::Pressed);
			keyboard->MapCommandToButton(SDL_SCANCODE_G, std::make_unique<dae::MoveGridCommand>(scene->m_enemy, scene->m_Map, Direction::DOWN, true), dae::ButtonState::Pressed);
			keyboard->MapCommandToButton(SDL_SCANCODE_H, std::make_unique<dae::MoveGridCommand>(scene->m_enemy, scene->m_Map, Direction::RIGHT, true), dae::ButtonState::Pressed);

			keyboard->MapCommandToButton(SDL_SCANCODE_U, std::make_unique<dae::BreakMoveTileCommand>(scene->m_enemy,true), dae::ButtonState::Up);


			/////////////////////////////////////////////////////////


			input.m_PostClearCallback = [=]()
				{
					auto controller = InputManager::GetInstance().AddController();

					controller->MapCommandToThumbstick(dae::Controller::ControllerThumbsticks::LeftThumbstick, std::make_unique<dae::MoveGridCommand>(scene->m_player, scene->m_Map));
					controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonA, std::make_unique<dae::BreakMoveTileCommand>(scene->m_player), dae::ButtonState::Up);


					auto controller2 = InputManager::GetInstance().AddController();
					controller2->MapCommandToThumbstick(dae::Controller::ControllerThumbsticks::LeftThumbstick, std::make_unique<dae::MoveGridCommand>(scene->m_enemy, scene->m_Map));
					controller2->MapCommandToButton(dae::Controller::ControllerButtons::ButtonA, std::make_unique<dae::BreakMoveTileCommand>(scene->m_enemy,true), dae::ButtonState::Up);
				};

			dae::SoundSystem& audio{ dae::Audio::Get() };
			audio.Play(s_MenuMusicId, 0.2f, 100);


		}
	
	}
}

void dae::OpenLevelCommand::AddKeyBindOnePerson(dae::Keyboard * keyboard, dae::Scene* scene, dae::InputManager& input)
{
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
	audio.Play(s_MenuMusicId, 0.2f, 100);
}

void dae::OpenLevelCommand::Undo()
{
}
