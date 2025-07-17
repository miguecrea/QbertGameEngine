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

	


}

void dae::restartGameCommand::Undo()
{
}
