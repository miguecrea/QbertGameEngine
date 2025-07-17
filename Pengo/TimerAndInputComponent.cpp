#include "TimerAndInputComponent.h"
#include"SceneManager.h"

dae::TimerAndInputComponent::TimerAndInputComponent()
{
}

void dae::TimerAndInputComponent::Update()
{
	HandleInputBlocking();
}

void dae::TimerAndInputComponent::HandleInputBlocking()
{
	if (m_startTimer)
	{
		StartCount();
	}
	if (IsTimerDone())
	{
		ResetTimer();
	}
}

void dae::TimerAndInputComponent::ResetTimer()
{
	m_CanUseInput = true;
	m_startTimer = false;
	m_TimerUntilUsingInput = 0;
}

void dae::TimerAndInputComponent::Render()
{
}

void dae::TimerAndInputComponent::StartCount()
{
	m_CanUseInput = false;
	m_TimerUntilUsingInput += SceneManager::GetInstance().GetDeltaTime();
}

void dae::TimerAndInputComponent::StartTimer()
{
	m_startTimer = true;
}

bool dae::TimerAndInputComponent::GetCanUseInput() const
{
	return m_CanUseInput;
}

void dae::TimerAndInputComponent::setCanUseInput(bool value)
{
	m_CanUseInput = value;
}

bool dae::TimerAndInputComponent::IsTimerDone()
{
	return m_TimerUntilUsingInput >= m_TimeUntilUsingInput;
}
