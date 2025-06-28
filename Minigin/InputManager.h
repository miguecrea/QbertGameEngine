#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>
#include "Controller.h"
#include "Keyboard.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>   //make it  a singletonm    
	{
	public:
		InputManager();
		void ClearCommands();

		void ClearSpecificControllerAndKeyboard();
		bool ProcessInput();
		Controller * AddController(); 
		Keyboard * GetKeyboard();  

		void ClearControllCommands();

	private:
		std::vector<std::unique_ptr<Controller>> m_pControllers{};
		Keyboard m_Keyboard;
	};

}
