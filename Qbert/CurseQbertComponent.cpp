#include "CurseQbertComponent.h"
#include"GameObject.h"
#include"RenderComponent.h"
#include"staticHeader.h"
dae::CurseQbertComponent::CurseQbertComponent(std::shared_ptr<dae::GameObject> Qbert):
	m_Qbert{Qbert}
{
}
void dae::CurseQbertComponent::Update()
{

	if (m_Qbert->GetComponent<dae::RenderComponent>()->IsVisible() == false) return;

	if (!s_CanUseInput)
	{
	this->GetOwner()->GetComponent<dae::RenderComponent>()->SetVisibility(true);

	}

	else 
	{
		this->GetOwner()->GetComponent<dae::RenderComponent>()->SetVisibility(false);
	}

}

void dae::CurseQbertComponent::Render()
{
}
