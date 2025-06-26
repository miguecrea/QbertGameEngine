#pragma once
#include <SDL.h>
#include <unordered_map>
#include <memory>
#include "Command.h"

namespace dae
{
	enum class ButtonState;

	class Keyboard final
	{
	public:
		Keyboard(const Uint8* pState);
		void Update(const SDL_Event& e);
		void UpdatePressed();

		void MapCommandToButton(SDL_Scancode button, std::unique_ptr<Command>&& pCommand, ButtonState state);
		void ClearCommands();

		void ClearWRSFkeys();
		std::vector<SDL_Scancode> m_keysToRemove{ SDL_SCANCODE_W,SDL_SCANCODE_R,SDL_SCANCODE_S,SDL_SCANCODE_F,SDL_SCANCODE_U};
		std::vector<SDL_Scancode> m_keysToRemove2{ SDL_SCANCODE_W,SDL_SCANCODE_R,SDL_SCANCODE_S,SDL_SCANCODE_F,SDL_SCANCODE_U};
	

	private:
		const Uint8 * m_pState;

		std::unordered_map<SDL_Scancode, std::unique_ptr<Command>, std::hash<SDL_Scancode>> m_pButtonUpCommands;
		std::unordered_map<SDL_Scancode, std::unique_ptr<Command>, std::hash<SDL_Scancode>> m_pButtonDownCommands;
		std::unordered_map<SDL_Scancode, std::unique_ptr<Command>, std::hash<SDL_Scancode>> m_pButtonPressedCommands;
	};
}

