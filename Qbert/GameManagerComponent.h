#pragma once

#include"Component.h"
#include<memory>

namespace dae
{
	class SceneManager;
	class MapComponent;
	class GameObject;
	class InputManager;
	class Scene;
	class Keyboard;

	class GameManagerComponent :public Component
	{

	public:

		GameManagerComponent(std::shared_ptr<GameObject> Map);
		virtual void BeginPlay() override;
		virtual void Render() override;
		virtual void Update() override;

	private:

		std::shared_ptr<GameObject> m_Map;
		void  TilesMatchedResponse();

		void LevelCompleted();

		void AddInputNameKeyBinds(InputManager & input,Scene * scene,Keyboard* keyboard);

		void AddKeyBinds(Keyboard* keyboard, dae::Scene* scene,InputManager& input);


	};


};