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
dae::OpenLevelCommand::OpenLevelCommand(std::vector<std::shared_ptr<dae::GameObject>> TextGameObjects,ChangeModeCommand * command):
	m_TextGameObjects{ TextGameObjects }, m_ChangeModeCommand{ command }
{
}

void dae::OpenLevelCommand::Execute()
{

	if (!m_ChangeModeCommand) return;

	
    int CurrentIndex = m_ChangeModeCommand->GetCurrentIndex();
	auto SaveLevelComppnent =  m_TextGameObjects[CurrentIndex]->GetComponent<dae::SaveLevelComponent>();
   
	if (SaveLevelComppnent)
	{
		SceneManager::GetInstance().SetCurrentScene(SaveLevelComppnent->GetLevelName());

		auto scene = SceneManager::GetInstance().GetCurrentScene();
	
		auto & input = dae::InputManager::GetInstance();
		input.m_ShouldClearController = true;

		if (SaveLevelComppnent->GetLevelName() == "SinglePlayerScene")
		{
			
		    input.m_PostClearCallback = [=]()
			{
				auto controller = InputManager::GetInstance().AddController();
				controller->MapCommandToThumbstick(dae::Controller::ControllerThumbsticks::LeftThumbstick,std::make_unique<dae::MoveGridCommand>(scene->m_player,scene->m_Map));
				controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonA,std::make_unique<dae::BreakMoveTileCommand>(scene->m_player),dae::ButtonState::Up);

			};

		}

	}
	dae::SoundSystem& audio{ dae::Audio::Get() };
	audio.Play(s_GameSoundId, 0.5f, 1);
}

void dae::OpenLevelCommand::Undo()
{
}
