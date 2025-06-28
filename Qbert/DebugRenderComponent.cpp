#include "DebugRenderComponent.h"
#include"Renderer.h"
#include"iostream"
void dae::MapComponent::BeginPlay()
{
}

void dae::MapComponent::Render()
{
	Renderer::GetInstance().FillSquare(100.f,100.f,100.f,100.f, SDL_Color{ 
		55,0,0,255});


	for (size_t Y = 0; Y < m_NumberTilesY; Y++)
	{
		for (size_t X = 0; X < m_NumberTilesX; X++)
		{
			Renderer::GetInstance().DrawSquare(0.f + m_TileSize * X, 0.f + m_TileSize * Y, m_TileSize, SDL_Color{55,0,0,255 });
		}
	}
}

void dae::MapComponent::Update()
{

	

}
