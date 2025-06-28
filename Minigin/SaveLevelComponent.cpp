#include "SaveLevelComponent.h"

dae::SaveLevelComponent::SaveLevelComponent(const std::string LevelName):
	m_levelName{LevelName}
{
}

void dae::SaveLevelComponent::Update()
{
}

void dae::SaveLevelComponent::Render()
{
}

std::string dae::SaveLevelComponent::GetLevelName()
{
	return m_levelName;
}
