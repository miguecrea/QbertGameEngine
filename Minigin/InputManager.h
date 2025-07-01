#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>
#include "Controller.h"
#include "Keyboard.h"
#include<functional>

namespace dae
{
	class InputManager final : public Singleton<InputManager>  
	{
	public:
		InputManager();
		void ClearCommands();

		void ClearSpecificControllerAndKeyboard();
		bool ProcessInput();
		Controller * AddController(); 
		Keyboard * GetKeyboard();  


		bool m_ShouldClearController = false;
		std::function<void()> m_PostClearCallback{};

	private:
		std::vector<std::unique_ptr<Controller>> m_pControllers{};
		Keyboard m_Keyboard;
	};

}
