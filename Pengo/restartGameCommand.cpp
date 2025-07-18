#include "restartGameCommand.h"
#include"iostream"
#include"SceneManager.h"
#include"Tags.h"
#include"staticHeader.h"
#include"OpenLevelCommand.h"
#include"ChangeModeCommand.h"
#include"Scene.h"
#include <cstdlib> // for exit()
dae::restartGameCommand::restartGameCommand()
{
}

void dae::restartGameCommand::Execute()
{
	SceneManager::GetInstance().SetCurrentScene(SINGLE_PLAYER_SCENE);
	s_ResetGame = true;
	std::exit(0);
}

void dae::restartGameCommand::Undo()
{
}
