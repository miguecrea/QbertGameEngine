#include "NextSceneCommand.h"
#include "SceneManager.h"
#include "Scene.h"
#include"staticHeader.h"
#include"SoundSystem.h"
#include"Audio.h"
#include"InputManager.h"
#include"GameObject.h"
#include <memory>
#include"AddInput.h"
#include"Tags.h"
#include"MoveGridCommand.h"
#include"BreakMoveTileCommand.h"
#include"restartGameCommand.h"
dae::NextSceneCommand::NextSceneCommand(const std::string& nameScene, GameMode gamemode) :
	nameOfScene{ nameScene },
	m_gameMode{ gamemode }
{
}

void dae::NextSceneCommand::Execute()
{

	auto& input = InputManager::GetInstance();
	SceneManager::GetInstance().SetCurrentScene(nameOfScene);
	auto scene = SceneManager::GetInstance().GetCurrentScene();

	input.ClearSpecificControllerAndKeyboard();
	input.m_ShouldClearController = true;
	auto keyboard = input.GetKeyboard();


	if (nameOfScene == SINGLE_PLAYER_SCENE)  // o si es level idk if level 2 maybe in the other with keybaord
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
		audio.Play(s_MenuMusicId, 0.5f, 100);


	}
	else if (nameOfScene == CO_OP_SCENE)
	{
		//add kyabord an controller formplayer 2
		//needs to be set on scene


	}
	else if (nameOfScene == VERSUS_MODE)
	{
		// and keybaord and controller for enemy 
		//needs to be scene.addEndmy 

	}
	else if (nameOfScene == SCORE_SCENE)
	{
		// add binding to restart 

		dae::SoundSystem& audio{ dae::Audio::Get() };
		audio.Play(S_ScoresSceneSound, 0.5f,0);


		input.m_PostClearCallback = [=]()
			{
				auto controller = InputManager::GetInstance().AddController();
				controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonB, std::make_unique<dae::restartGameCommand>(), dae::ButtonState::Up);
			};


		//restart game 
		//add  binding to go back o the beginning 
	}



}

void dae::NextSceneCommand::Undo()
{
}
