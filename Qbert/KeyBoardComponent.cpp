#include "KeyBoardComponent.h"
#include"Renderer.h"
#include"GameObject.h"
#include"TextComponent.h"

dae::KeyBoardComponent::KeyBoardComponent(const char& key, std::shared_ptr< TextComponent> textComponent) :
	m_key{ key }, m_pTextComponent{ textComponent }
{
}

dae::KeyBoardComponent::~KeyBoardComponent()
{
}

void dae::KeyBoardComponent::Render()
{
	Renderer::GetInstance().DrawSquare(GetOwner()->GetLocalPosition().x , GetOwner()->GetLocalPosition().y , 40, SDL_Color{ 255,255,255,255 });

	if (m_IsActive)
	{
		Renderer::GetInstance().FillSquare(GetOwner()->GetLocalPosition().x , GetOwner()->GetLocalPosition().y , 40, SDL_Color{ 0,0,255,100 });

	}

}

void dae::KeyBoardComponent::Update()
{
	if (m_pTextComponent)
	{
		m_pTextComponent->SetTextToTexture(std::string(1, m_key));
	}

}