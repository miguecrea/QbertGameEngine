#include "TestCommand.h"
#include"InputManager.h"
#include"SceneManager.h"

dae::TestCommand::TestCommand()
{
}

void dae::TestCommand::Execute()
{

	auto& input = InputManager::GetInstance();
	input.m_ShouldClearController = true;
	SceneManager::GetInstance().SetCurrentScene("SinglePlayerScene");
	//auto scene  = SceneManager::GetInstance().GetCurrentScene();

	auto controller  = input.AddController();
	controller->DoNothing();
	//controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonB, std::make_unique<dae::MoveGridCommand>(MenuScene.m_player), dae::ButtonState::Up);


}
void dae::TestCommand::Undo()
{

}
