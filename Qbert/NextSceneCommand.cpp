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


dae::NextSceneCommand::NextSceneCommand(const std::string & nameScene, GameMode gamemode) :
	nameOfScene{ nameScene },
	m_gameMode{ gamemode }
{
}

void dae::NextSceneCommand::Execute()
{

	auto & input = InputManager::GetInstance();
	SceneManager::GetInstance().SetCurrentScene(nameOfScene);

	auto scene = SceneManager::GetInstance().GetCurrentScene(); 
	input.ClearSpecificControllerAndKeyboard();

	//if (nameOfScene != SCORE_SCENE && nameOfScene != INPUT_NAME_SCENE)
	//{
	//	auto render = scene->m_player->GetComponent<dae::RenderComponent>();
	//	AddControllerKeyboardPlayer1(scene->m_player, render);
	//}
	//if (nameOfScene == CO_OP_SCENE)
	//{
	//	auto render2Player = scene->m_player2->GetComponent<dae::RenderComponent>();
	//	AddControllerKeyboardPlayer2(scene->m_player2, render2Player);
	//	s_Lives = 7;
	//}

	//if (nameOfScene == VERSUS_MODE)   //veruss
	//{
	//	auto render2Player = scene->m_enemy->GetComponent<dae::RenderComponent>();
	//	AddControllerKeyboardPlayer2(scene->m_enemy, render2Player);
	//	s_Lives = 7;
	//}

	dae::SoundSystem& audio{ dae::Audio::Get() };
	audio.Play(s_GameSoundId, 0.5f, 1);
}

void dae::NextSceneCommand::Undo()
{
}
