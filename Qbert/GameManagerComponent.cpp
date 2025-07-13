#include "GameManagerComponent.h"
#include"DebugRenderComponent.h"
#include"GameObject.h"
#include"Audio.h"
#include"staticHeader.h"
dae::GameManagerComponent::GameManagerComponent(std::shared_ptr<GameObject> Map):
	m_Map{Map}
{
}

void dae::GameManagerComponent::BeginPlay()
{

	auto MapComponent = m_Map->GetComponent<dae::MapComponent>();

	MapComponent->m_On3TilesMatched.Add(std::bind(&GameManagerComponent::TilesMatchedResponse, this));
}

void dae::GameManagerComponent::Render()
{
}

void dae::GameManagerComponent::Update()
{
}

void dae::GameManagerComponent::TilesMatchedResponse()
{

	dae::SoundSystem& audio{ dae::Audio::Get() };
	audio.Play(S_CubesAligned, 1.f, 3);



	std::cout << " DELEGATE 3 TILES MATCHED\n";
}
