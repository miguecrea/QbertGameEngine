#pragma once

#include"Component.h"
#include"memory"
#include"vector"
#include"SDL.h"
#include<string>
namespace dae
{


	class CollisionComponent : public Component
	{
	public:
		
		enum class WhichDificulty
		{
			Dificulty1 = 1 ,
			Dificulty2 = 2,
			Dificulty3 = 2

		};

		WhichDificulty m_dificultyEnum{ WhichDificulty::Dificulty1 };

		CollisionComponent(std::vector<std::shared_ptr<dae::GameObject>> & enemiesandMap,int dificulty,std::vector<std::shared_ptr<dae::GameObject>>& enemies);  //make collider width dimensions
		void InitializeMap();
		virtual ~CollisionComponent();
		CollisionComponent(const CollisionComponent& other) = default;
		CollisionComponent(CollisionComponent&& other) = default;
		CollisionComponent& operator=(const CollisionComponent& other) = default;
		CollisionComponent& operator=(CollisionComponent&& other) = default;

		virtual void Render() override;
		virtual void Update() override;
		virtual void BeginPlay() override;

		void CheckCollision(SDL_Rect& selfRect);
		void ChangeScene();
		void Dificulty1(SDL_Rect& selfRect, int i);
		void Dificulty2(SDL_Rect& selfRect, int i);
		void Dificulty3(SDL_Rect& selfRect, int i);

		void SetFallingVariable(bool isFalling);
		bool IsFalling();
		bool HasLevelBeenComplete(int index);
		bool IsSameScene(const std::string& scenename);
		void OpenScene(const std::string& scenename);


	private:
		bool Collides(const SDL_Rect& self,const SDL_Rect & objects);  
		bool m_canCollide = true;
	
		std::shared_ptr<GameObject> m_Owner = nullptr;
		std::vector<std::shared_ptr<GameObject>> m_Map;
		std::vector<std::shared_ptr<GameObject>> m_Enemies;

		bool m_Isfalling = false;
		int m_dificulty = 1;
		int m_cubeIndex = 0;
		bool m_canAddScore = true;
		bool m_hasCollidedWithEnemies = false;
		float m_TimerUntilRestarting = 0.0f;
		bool m_startTimer = false;

		int m_ScoreAdded = 25;
		int m_ScoreAddedLevel2 = 30;
		int m_ScoreAddedLevel3 = 40;
		float MAX_TIME_UNTIL_RESTARTING = 3.f;


	};


}