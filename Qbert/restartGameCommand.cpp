#include "restartGameCommand.h"
#include"iostream"
#include"SceneManager.h"
#include"Tags.h"
#include"staticHeader.h"
#include"OpenLevelCommand.h"
#include"ChangeModeCommand.h"
#include"Scene.h"
dae::restartGameCommand::restartGameCommand()
{
}

void dae::restartGameCommand::Execute()
{
	SceneManager::GetInstance().SetCurrentScene(SINGLE_PLAYER_SCENE);
	s_ResetGame = true;

	std::cout << "Game Restarted<<\n";

	//auto scene = SceneManager::GetInstance().GetCurrentScene();

	//s_Lives = m_MaxLives;
	////s lives set back to 3 


	//std::unique_ptr<dae::ChangeModeCommand> ChangeMode = std::make_unique<dae::ChangeModeCommand>(scene->TTextGameObjects);
	//std::unique_ptr<dae::OpenLevelCommand> OpenLevelCommand = std::make_unique<dae::OpenLevelCommand>(TextGameObjects, ChangeMode.get());

	//controller->MapCommandToThumbstick(dae::Controller::ControllerThumbsticks::LeftThumbstick, std::move(ChangeMode));
	//controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonA, std::move(OpenLevelCommand), dae::ButtonState::Up);




}

void dae::restartGameCommand::Undo()
{
}
