#pragma once


#pragma once
#include "Component.h"
#include "TextComponent.h"
#include<string>

namespace dae
{
	class GameObject;

	class DisplayNameComponent final :public Component
	{
	public:

		virtual void Update() override;
		DisplayNameComponent(std::shared_ptr<TextComponent> pTextComponent = nullptr);


		virtual ~DisplayNameComponent() = default;
		DisplayNameComponent(const DisplayNameComponent& other) = default;
		DisplayNameComponent(DisplayNameComponent&& other) = default;
		DisplayNameComponent& operator=(const DisplayNameComponent& other) = default;
		DisplayNameComponent& operator=(DisplayNameComponent&& other) = default;

		void writeMaxScore(const std::string& filename, int score, const std::string& playerName);
		std::pair<int, std::string> readMaxScore(const std::string& filename);
		
		bool m_IsScore = false;
		bool m_IsName = false;
		bool m_IsHighestScore = false;
		bool m_IsLives = false;
	private:
		std::shared_ptr<TextComponent> m_pTextComponent;

	};
}
