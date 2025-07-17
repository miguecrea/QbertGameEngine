#include "GameManagerComponent.h"
#include"DebugRenderComponent.h"
#include"GameObject.h"
#include"Audio.h"
#include"staticHeader.h"
#include"EnemySpawner.h"
#include"SceneManager.h"
#include"Scene.h"
#include"Tags.h"
#include"InputManager.h"
#include"MoveGridCommand.h"
#include"BreakMoveTileCommand.h"
#include"NextSceneCommand.h"
#include"LockInCommand.h"
#include"ChangeSelectionCommand.h"
#include"InputManager.h"

dae::GameManagerComponent::GameManagerComponent(std::shared_ptr<GameObject> Map) :
	m_Map{ Map }
{
}

void dae::GameManagerComponent::BeginPlay()
{

	auto MapComponent = m_Map->GetComponent<dae::MapComponent>();

	MapComponent->m_On3TilesMatched.Add(std::bind(&GameManagerComponent::TilesMatchedResponse, this));

	auto EnemyManagerComponent = this->GetOwner()->GetComponent<dae::EnemySpawner>();
	EnemyManagerComponent->m_GameOver.Add(std::bind(&GameManagerComponent::LevelCompleted, this));
}

void dae::GameManagerComponent::Render()
{
}

void dae::GameManagerComponent::Update()
{
}

void dae::GameManagerComponent::TilesMatchedResponse()
{
	dae::SoundSystem& audio{ dae::Audio::Get() };
	audio.Play(S_CubesAligned, 0.2f, 1);
	std::cout << " DELEGATE 3 TILES MATCHED\n";
}

void dae::GameManagerComponent::LevelCompleted()
{

	auto scene = SceneManager::GetInstance().GetCurrentScene();

	auto& input = dae::InputManager::GetInstance();
	auto keyboard{ input.GetKeyboard() };   //second uses keyboard 
	input.ClearSpecificControllerAndKeyboard();
	input.m_ShouldClearController = true;



	if (scene->GetName() == SINGLE_PLAYER_SCENE)
	{
	     SceneManager::GetInstance().SetCurrentScene(LEVEL_2);
		auto newScene = SceneManager::GetInstance().GetCurrentScene();

		AddKeyBinds(keyboard, newScene, input);

	}
	else if(scene->GetName() == LEVEL_2)
	{
		SceneManager::GetInstance().SetCurrentScene(LEVEL_3);
		auto newScene = SceneManager::GetInstance().GetCurrentScene();
		AddKeyBinds(keyboard, newScene, input);
	}
	else if (scene->GetName() == LEVEL_3)
	{
		SceneManager::GetInstance().SetCurrentScene(INPUT_NAME_SCENE);
		auto newScene = SceneManager::GetInstance().GetCurrentScene();
		AddInputNameKeyBinds(input, newScene, keyboard);

		dae::SoundSystem& audio{ dae::Audio::Get() };
		audio.Play(S_PengoDeath, 0.5f, 0);
	}
	else if (scene->GetName() == CO_OP_SCENE || scene->GetName() == VERSUS_MODE)
	{
		SceneManager::GetInstance().SetCurrentScene(INPUT_NAME_SCENE);
		auto newScene = SceneManager::GetInstance().GetCurrentScene();
		AddInputNameKeyBinds(input, newScene, keyboard);

		dae::SoundSystem& audio{ dae::Audio::Get() };
		audio.Play(S_PengoDeath, 0.5f, 0);
	}



	
}

void dae::GameManagerComponent::AddInputNameKeyBinds(dae::InputManager & input, dae::Scene* scene, dae::Keyboard* keyboard)
{

	input.m_PostClearCallback = [=]()
		{
			auto controller = InputManager::GetInstance().AddController();
			controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonA, std::make_unique<dae::LockInCommand>(scene->m_Obejects), dae::ButtonState::Up);
			controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonY, std::make_unique<dae::NextSceneCommand>(SCORE_SCENE, GameMode::Versus), dae::ButtonState::Up);

			controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadUp, std::make_unique<dae::ChangeSelectionCommand>(scene->m_Obejects, 0, Direction::UP), dae::ButtonState::Up);
			controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadLeft, std::make_unique<dae::ChangeSelectionCommand>(scene->m_Obejects, 0, Direction::LEFT), dae::ButtonState::Up);
			controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadRight, std::make_unique<dae::ChangeSelectionCommand>(scene->m_Obejects, 0, Direction::RIGHT), dae::ButtonState::Up);
			controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadDown, std::make_unique<dae::ChangeSelectionCommand>(scene->m_Obejects, 0, Direction::DOWN), dae::ButtonState::Up);

		};

	keyboard->MapCommandToButton(SDL_SCANCODE_5, std::make_unique<dae::NextSceneCommand>(SCORE_SCENE, GameMode::Versus), dae::ButtonState::Up);

}

void dae::GameManagerComponent::AddKeyBinds(dae::Keyboard* keyboard, dae::Scene* scene, dae::InputManager& input)
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
