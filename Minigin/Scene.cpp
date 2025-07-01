#include "Scene.h"
#include "GameObject.h"
#include <algorithm>
#include"InputManager.h"
#include"RenderComponent.h"


using namespace dae;

unsigned int Scene::m_idCounter = 0;


Scene::Scene(const std::string& name)
	: m_name(name)

{
}

void dae::Scene::SetId(int number)
{
	m_id = number;
}

int dae::Scene::GetId() const
{
	return m_id;
}

Scene::~Scene() = default;

class GameObjectAlreadyHasParentException {};

void Scene::Add(std::shared_ptr<GameObject> object) 
{
	if (object->GetParent())
	{
		throw GameObjectAlreadyHasParentException{};
	}

	if (std::find(m_pObjects.begin(), m_pObjects.end(), object) != m_pObjects.end())
	{
		throw GameObjectAlreadyHasParentException{};
	}

	m_pObjects.emplace_back(std::move(object));

	//Sort the components based on priority
	auto compareFunction = [&](const std::shared_ptr<GameObject>& pLhs, const std::shared_ptr<GameObject>& pRhs)
	{
		return pRhs->GetPriority() < pLhs->GetPriority();
	};

	std::sort(m_pObjects.begin(), m_pObjects.end(), compareFunction);
}

void dae::Scene::ForceRemoveAll()
{
	m_pObjects.clear();         
}

void dae::Scene::DestroyAll()
{
	for (const auto& pObject : m_pObjects)
	{
		pObject->Destroy();

	}
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_pObjects.erase(std::remove(m_pObjects.begin(), m_pObjects.end(), object), m_pObjects.end());
}

void Scene::RemoveAll()
{
	m_pObjects.clear();
}

void Scene::Update()
{
	for(auto& pObject : m_pObjects)
	{
		if (!pObject->IsDestroyed())
		{
			pObject->Update();
		}
	}

}

void dae::Scene::FixedUpdate()
{
	for (auto& pObject : m_pObjects)
	{
		pObject->FixedUpdate();
	}
}

std::string dae::Scene::GetName() const
{
	return m_name;
}

void dae::Scene::Load()
{

}

bool dae::Scene::NeedsCleanUp() const
{

	return false;
}

void dae::Scene::AddPlayer(std::shared_ptr<GameObject> player)
{

	m_player = player;
}

void dae::Scene::AddPlayer2(std::shared_ptr<GameObject> player)
{
	
	m_player2 = player;
}

void dae::Scene::AddMap(std::shared_ptr<GameObject> map)
{
	m_Map = map;
}

void dae::Scene::AddEnemy(std::shared_ptr<GameObject> player)
{
	m_enemy = player;
}

std::shared_ptr<dae::RenderComponent> dae::Scene::GetPlayerRenderComponent()
{
	return m_player->GetComponent<dae::RenderComponent>();
}

void Scene::Render() const
{
	for (const auto& pObject : m_pObjects)
	{
		pObject->Render();
	}
}

void dae::Scene::BeginPlay()
{

	for (const auto& pObject : m_pObjects)
	{
		pObject->BeginPlay();
	}
}


void dae::Scene::CleanUp()
{

	



}
