#include "ChangeModeCommand.h"
#include"GameObject.h"
#include"TextComponent.h"
#include"SDL.h"
#include<iostream>
#include"SceneManager.h"

dae::ChangeModeCommand::ChangeModeCommand(std::vector<std::shared_ptr<dae::GameObject>>TextGameObjects) :
	m_TextGameObejects{ TextGameObjects }
{
	m_VectorSize = static_cast<int>(m_TextGameObejects.size());

	auto TextComponent = m_TextGameObejects[0]->GetComponent<dae::TextComponent>()->m_ShowRectangle = true;
}

void dae::ChangeModeCommand::Execute()
{

	m_Counter += SceneManager::GetInstance().GetDeltaTime();

	if (m_Counter >= m_TimeUntilCallingAgain)
	{
		m_Counter = 0;
		ChangeNextOne();
	}
}

void dae::ChangeModeCommand::ChangeNextOne()
{
	std::cout << "Change Next one " << m_Index << "\n";

	auto TextComponent = m_TextGameObejects[m_Index]->GetComponent<dae::TextComponent>();
	if (TextComponent)
	{
		TextComponent->m_ShowRectangle = false;
	}

	m_Index = (m_Index + 1) % m_VectorSize;

	auto TextComponent2 = m_TextGameObejects[m_Index]->GetComponent<dae::TextComponent>();

	if (TextComponent2)
	{
		TextComponent2->m_ShowRectangle = true;

	}


}

void dae::ChangeModeCommand::Undo()
{
}

int dae::ChangeModeCommand::GetCurrentIndex()
{
	return m_Index;
}
