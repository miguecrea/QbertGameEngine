#include "LivesComponent.h"


#include "TextComponent.h"
#include <iostream>
#include "EventManager.h"
#include"GameObject.h"
#include"staticHeader.h"
#include"SceneManager.h"
#include"InputManager.h"
#include"Tags.h"
#include"Audio.h"
#include"LockInCommand.h"
#include"ChangeSelectionCommand.h"
#include"PengoDirection.h"
#include"Scene.h"
#include"NextSceneCommand.h"

dae::LivesComponent::LivesComponent()
{
}

dae::LivesComponent::~LivesComponent()
{
}

void dae::LivesComponent::BeginPlay()
{

	// this->GetOwner()


}

void dae::LivesComponent::Render()
{
}

void dae::LivesComponent::Update()
{

	if (m_StartTimer)
	{
		m_Timer += SceneManager::GetInstance().GetDeltaTime();
		if (m_Timer >= 3.f)
		{
			m_StartTimer = false;
			m_Timer = 0;

			dae::SoundSystem& audio{ dae::Audio::Get() };
			audio.Play(s_MenuMusicId, 0.5f, 0);

		}

	}

}

void dae::LivesComponent::DecreaseLive()
{

	//when you die 

	s_Lives--;

	m_StartTimer = true;

	dae::SoundSystem& audio{ dae::Audio::Get() };
	audio.Play(S_PengoDeath, 0.5f, 0);
	

	if (s_Lives <= 0)
	{
		SceneManager::GetInstance().SetCurrentScene(INPUT_NAME_SCENE);

		auto scene = SceneManager::GetInstance().GetCurrentScene();

		auto& input = dae::InputManager::GetInstance();
		input.ClearSpecificControllerAndKeyboard();
		input.m_ShouldClearController = true;


		auto keyboard = input.GetKeyboard();
		//should I add keyboard

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







}


