#include "SceneManager.h"
#include "Scene.h"
#include"Renderer.h"
#include<cassert>
#include"iostream"
#include"staticHeader.h"

void dae::SceneManager::Update(float deltaTime) 
{
	m_DeltaTime = deltaTime;
	m_CurrentScene->Update();

}

void dae::SceneManager::FixedUpdate(float fixedTimeStep) 
{
	m_FixedTimeStep = fixedTimeStep;

	m_CurrentScene->FixedUpdate();
}

void dae::SceneManager::Render() const 
{

	m_CurrentScene->Render();
	
}

void dae::SceneManager::BeginPlay()
{
	m_CurrentScene->BeginPlay();

}

void dae::SceneManager::CleanUp()
{

	for (auto& pScene : m_pScenes)
	{
		if (pScene->NeedsCleanUp())
		{
			pScene->CleanUp();                          
		}
	}
}

float dae::SceneManager::GetDeltaTime() const
{
	return m_DeltaTime;
}

float dae::SceneManager::GetFixedTimeStep() const
{
	return m_FixedTimeStep;
}

float dae::SceneManager::GetFramePercentage() const
{
	return m_FramePercentage;
}

dae::Scene * dae::SceneManager::GetCurrentScene() const
{
	return m_CurrentScene;
}

dae::Scene* dae::SceneManager::GetScene(const std::string& name) const
{
	auto pScene{ std::find_if(m_pScenes.begin(), m_pScenes.end(), [&](std::shared_ptr<Scene> pScene) { return pScene->GetName() == name; }) };

	assert(pScene != m_pScenes.end());

	return (*pScene).get();
}

void dae::SceneManager::SetCurrentScene(const std::string& name)
{

	//call the Begin Play ,but every time we set the scene it would be called 
	auto pScene{ std::find_if(m_pScenes.begin(), m_pScenes.end(), [&](std::shared_ptr<Scene> pScene) { return pScene->GetName() == name; }) };

	if (pScene != m_pScenes.end())
	{
		m_CurrentScene = (*pScene).get();

		//if (!BgeinPlayAlreadyRun)
		//{

		//if (m_CurrentScene->GetName() == "SinglePlayerScene")
		//{
		m_CurrentScene->BeginPlay();

	//	}

		//}


	}
}

void dae::SceneManager::ForceRemoveAllObjects()
{

	for (auto& pScene : m_pScenes)
	{
		pScene->ForceRemoveAll();   
	}

}



dae::Scene & dae::SceneManager::CreateScene(const std::string& name)
{
	const auto & scene = std::shared_ptr<Scene>(new Scene(name));
	m_pScenes.push_back(scene);
	m_CurrentScene = scene.get();  
	return * scene;
}
