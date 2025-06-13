#include "FreeFallComponent.h"
#include"GameObject.h"
#include"iostream"
#include"SceneManager.h"
dae::FreeFallComponent::FreeFallComponent()
{

}

void dae::FreeFallComponent::Update()
{
	glm::vec3 m_OldPosition = GetOwner()->GetLocalPosition();
	if (m_IsActive)
	{
		m_deltaTime = SceneManager::GetInstance().GetDeltaTime();

		// Update velocity (v = u + at)
		m_VelocityY += GRAVITY * m_deltaTime;

		// Update position (s = ut + 0.5at^2)
		m_OldPosition.y += -(m_VelocityY * m_deltaTime + 0.5f * GRAVITY * m_deltaTime * m_deltaTime);
		GetOwner()->SetPosition(m_OldPosition.x, m_OldPosition.y);
	}
}

void dae::FreeFallComponent::Render()
{
}

void dae::FreeFallComponent::SetActive(bool value)
{
	m_IsActive = value;
}

void dae::FreeFallComponent::SetUnactive()
{
	m_IsActive = false;
	m_deltaTime = 0;
	m_VelocityY = 0;

}

