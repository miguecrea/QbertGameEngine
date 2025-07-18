#include "PengoComponent.h"
#include"GameObject.h"
dae::PengoComponent::PengoComponent()
{
}

void dae::PengoComponent::BeginPlay()
{
}

void dae::PengoComponent::Render()
{


	float Size{ 40.f };
	for (size_t i = 0; i < 10; i++)
	{
	Renderer::GetInstance().FillSquare(0 + Size * i,0, Size, SDL_Color{0,0,0,250});

	}

}
