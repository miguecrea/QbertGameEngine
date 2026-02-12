#include "FPSComponent.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include <string>
#include <iostream>
#include"staticHeader.h"
dae::FPSComponent::FPSComponent(std::shared_ptr<TextComponent> pTextComponent, float waitingTime, int priority)
	:Component(priority), m_pTextComponent{ pTextComponent }, m_RefreshTime{ std::max(0.f, waitingTime) }
{
}
void dae::FPSComponent::Update()
{
	const float deltaTime{ SceneManager::GetInstance().GetDeltaTime() };

	++m_NrFrames;
	m_ElapsedTime += deltaTime;

	if (m_ElapsedTime >= m_RefreshTime)
	{
		const int currentFrameRate{ static_cast<int>(m_NrFrames / m_ElapsedTime) };
		//Dirty flag
		if (currentFrameRate != m_FrameRate)
		{
			m_FrameRate = currentFrameRate;
			const std::string frameRateString{ std::to_string(m_FrameRate) + " FPS" };
			if (m_pTextComponent)
			{
				m_pTextComponent->SetTextToTexture(frameRateString);
			}
		}
		m_NrFrames = 0;
		m_ElapsedTime = 0.f;
	}
}






//////////////////////////////////////////////////////////////////


dae::RenderLivesComponent::RenderLivesComponent(bool isScore, std::shared_ptr<TextComponent> pTextComponent, int priority)
	:Component(priority), m_pTextComponent{ pTextComponent }, m_IsScore{ isScore }
{
}
void dae::RenderLivesComponent::Update()
{
	if (m_pTextComponent)
	{
		if (m_IsScore)
		{
			m_pTextComponent->SetTextToTexture("Score is " + std::to_string(s_Score));
		}
		else
		{
			m_pTextComponent->SetTextToTexture("Lives Remanining " + std::to_string(s_Lives));
		}
	}

}