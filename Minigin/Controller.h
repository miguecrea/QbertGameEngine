#pragma once
#include <memory>
#include <unordered_map>

namespace dae
{
	class Command;
	enum class ButtonState;

	class Controller final
	{
	public:
		enum class ControllerButtons
		{
			DPadUp = 0x0001,
			DPadDown = 0x0002,
			DPadLeft = 0x0004,
			DPadRight = 0x0008,

			Start = 0x0010,
			Back = 0x0020,

			LeftThumbstick = 0x0040,
			RightThumbstick = 0x0080,

			LeftBumper = 0x0100,
			RightBumper = 0x0200,

			ButtonA = 0x1000,
			ButtonB = 0x2000,
			ButtonX = 0x4000,
			ButtonY = 0x8000
		};

		void Update();
		
		bool IsDown(ControllerButtons button) const;
		bool IsUp(ControllerButtons button) const;
		bool IsPressed(ControllerButtons button) const;

		void MapCommandToButton(ControllerButtons button, std::unique_ptr<Command>&& pCommand, ButtonState state);

		explicit Controller(int controllerIndex);
		~Controller();

		Controller(Controller&&) = default;
		Controller& operator=(Controller&&) = default;

	private:
		class ControllerImpl;
		ControllerImpl* m_pImpl;

		//https://stackoverflow.com/questions/18837857/cant-use-enum-class-as-unordered-map-key
		std::unordered_map<ControllerButtons, std::unique_ptr<Command>, std::hash<ControllerButtons>> m_pButtonUpCommands;
		std::unordered_map<ControllerButtons, std::unique_ptr<Command>, std::hash<ControllerButtons>> m_pButtonDownCommands;
		std::unordered_map<ControllerButtons, std::unique_ptr<Command>, std::hash<ControllerButtons>> m_pButtonPressedCommands;
	};
}
