#include "TagComponent.h"
#include"GameObject.h"

dae::TagComponent::TagComponent(const std::string& tag):
	m_tag{tag}
{
}

void dae::TagComponent::Update()
{
}

void dae::TagComponent::Render()
{
}

std::string dae::TagComponent::GetTag()
{
	return m_tag;
}
