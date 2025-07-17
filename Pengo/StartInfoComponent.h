#pragma once
#include "Component.h"
#include <memory>
#include <cstdlib> // Include for std::exit()

namespace dae
{
	class GameObject;
	class Texture2D;
	class Font;

	class StartInfoComponent final : public Component
	{
	public:
		virtual void Render() override;

		StartInfoComponent(int priority = -2);
		virtual ~StartInfoComponent() = default;
		StartInfoComponent(const StartInfoComponent& other) = default;
		StartInfoComponent(StartInfoComponent&& other) = default;
		StartInfoComponent& operator=(const StartInfoComponent& other) = default;
		StartInfoComponent& operator=(StartInfoComponent&& other) = default;

		void ExitApplication()
		{
			std::exit(0);
		}

	};
}

