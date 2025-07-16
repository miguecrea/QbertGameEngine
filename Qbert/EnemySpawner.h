#pragma once

#include"Component.h"
#include<memory>
#include"vector"

namespace dae
{
	class SceneManager;
	class MapComponent;
	class GameObject;


	class EnemySpawner :public Component
	{

	public:

		int m_NumberActiveEnemies;

		EnemySpawner(std::vector<std::shared_ptr<dae::GameObject>> Tiles, std::shared_ptr<dae::GameObject > Map, std::shared_ptr<dae::GameObject> Pengo);

		virtual void BeginPlay();
		virtual void Render();
		virtual void Update();
	private:

		std::vector<std::shared_ptr<dae::GameObject>> m_Tiles;
		std::shared_ptr<dae::GameObject > m_Map;
		std::shared_ptr<dae::GameObject > m_Pengo;

		void SpawnEnemyCallBack(float x, float y);
		void SpawEnemy(float x, float y);




	
	};



};