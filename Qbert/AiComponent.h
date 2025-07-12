#pragma once
#include "Component.h"
#include"functional"
#include <memory>
#include <glm/glm.hpp>
#include<vector>



struct Node
{
	int y;
	int x;
	int parentX;
	int parentY;
	float gCost;
	float hCost;
	float fCost;
};


namespace dae
{
	class SceneManager;
	class MapComponent;


	class AIComponent :public Component
	{

	public:

		AIComponent(std::shared_ptr<GameObject> Map, std::shared_ptr<GameObject> pTargetGameObejct);
		virtual void BeginPlay() override;
		virtual void Render() override;
		virtual void Update() override;
	private:
		std::shared_ptr<GameObject> m_Map = nullptr;
		std::shared_ptr<GameObject> m_Target = nullptr;
		std::shared_ptr<MapComponent> m_mapComponent;
		dae::GameObject * m_Self = nullptr;
		float m_Speed = 20.f;

		float distanceBetweenPoints();

		SceneManager * m_pSceneManager;



		std::vector<Node> makePath(std::vector<std::vector<Node>> map, Node dest);
		bool isValid(int x, int y);
		std::vector<Node> aStar(Node agent, Node dest);

		std::vector<Node> m_usablePath;
		
		float m_TileSize = 48.f;

		int m_currentPathIndex{};
		bool m_movingToTarget = false;

		float UpdatePathTimer = 0.2f;
		bool m_CanUpdateFirstNode = true;

		glm::vec2 m_targetNode{};



	};


};