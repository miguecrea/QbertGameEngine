#pragma once

#include"Component.h"
#include<string>
namespace dae
{
	class GameObject;

	class SaveLevelComponent final : public Component
	{
	public:
		SaveLevelComponent(const std::string LevelName);
		virtual ~SaveLevelComponent() = default;
		SaveLevelComponent(const SaveLevelComponent& other) = default;
		SaveLevelComponent(SaveLevelComponent&& other) = default;
		SaveLevelComponent& operator=(const SaveLevelComponent& other) = default;
		SaveLevelComponent& operator=(SaveLevelComponent&& other) = default;

		void  Update() override;
		void  Render() override;
		std::string GetLevelName();

	private:

		std::string m_levelName;
	};
}