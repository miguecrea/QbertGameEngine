#include "OpenLevelCommand.h"
#include"ChangeModeCommand.h"
#include"GameObject.h"
#include"SaveLevelComponent.h"
#include"SceneManager.h"
#include"iostream"
#include"Audio.h"
#include"staticHeader.h"
#include"InputManager.h"

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

		
		auto & input = InputManager::GetInstance();

		input.ClearControllCommands();

		//input.ClearSpecificControllerAndKeyboard();

		//We need to Unmpa the bindings and map the other others // joystick and //the A 

		//based on level 

	}
	dae::SoundSystem& audio{ dae::Audio::Get() };
	audio.Play(s_GameSoundId, 0.5f, 1);
}

void dae::OpenLevelCommand::Undo()
{
}
