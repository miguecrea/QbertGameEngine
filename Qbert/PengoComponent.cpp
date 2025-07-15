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

	float X{};
	float Y{};
	Renderer::GetInstance().DrawSquare(this->GetOwner()->GetWorldPosition().x + 38.f, this->GetOwner()->GetWorldPosition().y,50.f, SDL_Color{255,255,255,250});

}
