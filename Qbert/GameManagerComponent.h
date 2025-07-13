#pragma once

#include"Component.h"
#include<memory>

namespace dae
{
	class SceneManager;
	class MapComponent;
	class GameObject;

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

	};


};