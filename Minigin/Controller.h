#pragma once
#include <memory>
#include"Command1D.h"
#include"Command2D.h"

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

		enum class ControllerTriggers
		{
			LeftTrigger,
			RightTrigger
		};

		enum class ControllerThumbsticks
		{
			LeftThumbstick,
			RightThumbstick
		};

		void Update();

		bool IsDown(ControllerButtons button) const;
		bool IsUp(ControllerButtons button) const;
		bool IsPressed(ControllerButtons button) const;

		void MapCommandToButton(ControllerButtons button, std::unique_ptr<Command>&& pCommand, ButtonState state);
		void MapCommandToTrigger(ControllerTriggers trigger, std::unique_ptr<Command1D>&& pCommand);
		void MapCommandToThumbstick(ControllerThumbsticks thumbstick, std::unique_ptr<Command2D>&& pCommand);
		//void MapCommandToThumbstick(ControllerThumbsticks thumbstick, const std::unique_ptr<Command2D> & pCommand);

		explicit Controller(int controllerIndex, bool invertY = true);
		~Controller();

		Controller(Controller&&) = default;
		Controller& operator=(Controller&&) = default;

		void ClearCommands();

			

	private:
		class ControllerImpl;
		ControllerImpl * m_pImpl;
	};
}
