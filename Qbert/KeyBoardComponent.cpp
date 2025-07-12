#include "KeyBoardComponent.h"
#include"Renderer.h"
#include"GameObject.h"
#include"TextComponent.h"

dae::KeyBoardComponent::KeyBoardComponent(const char& key, std::shared_ptr< TextComponent> textComponent,float TileSize) :
	m_key{ key }, m_pTextComponent{ textComponent },m_TileSize{ TileSize }
{
}

dae::KeyBoardComponent::~KeyBoardComponent()
{
}

void dae::KeyBoardComponent::Render()
{
	Renderer::GetInstance().DrawSquare(GetOwner()->GetWorldPosition().x , GetOwner()->GetWorldPosition().y , m_TileSize, SDL_Color{ 255,255,255,255 });

	if (m_IsActive)
	{
		Renderer::GetInstance().FillSquare(GetOwner()->GetWorldPosition().x , GetOwner()->GetWorldPosition().y , m_TileSize, SDL_Color{ 0,0,255,100 });

	}

}

void dae::KeyBoardComponent::Update()
{
	if (m_pTextComponent)
	{
		m_pTextComponent->SetTextToTexture(std::string(1, m_key));
	}

}