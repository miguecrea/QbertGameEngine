#pragma once
#include"Component.h"
#include<memory>
#include"SDL.h"
#include<string>
#include <unordered_set>
#include"DelegateBase.h"
#include<vector>

namespace dae
{
	class GameObject;
	class CollisionWithComponent final : public Component
	{
	public:

		CollisionWithComponent(std::vector<std::shared_ptr<GameObject>> & CollideObject);    /// vector
		virtual ~CollisionWithComponent() = default;
		CollisionWithComponent(const CollisionWithComponent& other) = default;
		CollisionWithComponent(CollisionWithComponent&& other) = default;
		CollisionWithComponent& operator=(const CollisionWithComponent& other) = default;
		CollisionWithComponent& operator=(CollisionWithComponent&& other) = default;
		void SetTutorial(bool isTutorial);

		bool Collides(const SDL_Rect& self, const SDL_Rect& objects);

		virtual void BeginPlay() override;
		void  Update() override;
		void  Render() override;
		void SetIsAi(bool isAi);
		bool IsAi();

	

		MulticastDelegate <std::string, std::string> m_OnCollisionEvent;
		std::unordered_set<size_t> m_CurrentlyCollidingTiles;
		std::shared_ptr<GameObject> m_CollideObject;
		bool m_IsTutorial = false;

		bool m_Active = false;

	private:




		std::vector<std::shared_ptr<GameObject>> m_CollideObjects;

		bool m_canCollide = true;
		static bool m_canPlaysound;
		float InitialPosX{ 98 };
		float InitialPosY{ 87 };
		float InitialPosXTutorial{ 96 };
		float InitialPosYTutorial{ 59 };
		int counter = 0;
		int m_musicCounter{};
		bool m_CanBroadCastEvent = false;
		bool m_canExecute = true;
		float m_timerUntilStoppingSquare = 0;
		bool m_DrawSqaure = false;
		float m_CollisionTimer = 0;
		bool m_startCounter = false;
		bool m_IsColliding = false;
		static bool m_HasTakenLifeOf;
		static int m_SnakePosIndex;
		bool m_IsAi = false;
		float m_TimeToRespawn = 0;
		bool m_enemyCollides = false;

	};
}