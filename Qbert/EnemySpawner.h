#pragma once

#include"Component.h"
#include<memory>

namespace dae
{
	class SceneManager;
	class MapComponent;
	class GameObject;


	class EnemySpawner :public Component
	{

	public:

		EnemySpawner();
		std::shared_ptr<GameObject> m_Map = nullptr;
	
	};


};