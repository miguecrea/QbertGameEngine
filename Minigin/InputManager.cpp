#include <SDL.h>
#include "InputManager.h"
#include "imgui_impl_sdl2.h"
#include"iostream"

using namespace dae;

InputManager::InputManager()
	:m_Keyboard{ SDL_GetKeyboardState(nullptr) }
{
}

void dae::InputManager::ClearCommands()
{
	m_Keyboard.ClearCommands();

	m_pControllers.clear();
	
}

void dae::InputManager::ClearSpecificControllerAndKeyboard()
{

	m_Keyboard.ClearWRSFkeys();

	//m_pControllers.clear();  


}

bool InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) 
		{
			return false;
		}

		if (e.key.repeat == 0)
		{
			m_Keyboard.Update(e);
		}

		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	m_Keyboard.UpdatePressed();

	for (auto & pController : m_pControllers)
	{
		pController->Update();
	}

	if (m_ShouldClearController)
	{
		m_ShouldClearController = false;
		m_pControllers.clear();


		if(m_PostClearCallback)
		{
			m_PostClearCallback();
			m_PostClearCallback = nullptr;
		}

	}


	

	return true;
}

Controller * dae::InputManager::AddController()
{
	const int index{ static_cast<int>(m_pControllers.size()) };
	m_pControllers.push_back(std::make_unique<Controller>(index));

	return m_pControllers.back().get();
}

Keyboard* dae::InputManager::GetKeyboard()
{
	return &m_Keyboard;
}

