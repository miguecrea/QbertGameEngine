#pragma once
#include"Component.h"
#include<memory>
#include"SDL.h"
#include<string>
#include <unordered_set>
#include"DelegateBase.h"

namespace dae
{
	class GameObject;
	class CollisionWithComponent final : public Component
	{
	public:

		CollisionWithComponent(std::shared_ptr<GameObject>& CollideObject);    /// vector
		virtual ~CollisionWithComponent() = default;
		CollisionWithComponent(const CollisionWithComponent& other) = default;
		CollisionWithComponent(CollisionWithComponent&& other) = default;
		CollisionWithComponent& operator=(const CollisionWithComponent& other) = default;
		CollisionWithComponent& operator=(CollisionWithComponent&& other) = default;
		void SetTutorial(bool isTutorial);

		//bool IsActive() const { return m_IsActive;  }
		bool Collides(const SDL_Rect& self, const SDL_Rect& objects);

		virtual void BeginPlay() override;
		void  Update() override;
		void  Render() override;
		void SetIsAi(bool isAi);
		bool IsAi();

		bool AddPossibleCollidedObject(std::shared_ptr<GameObject>& collideObject);
		bool RemovePossibleCollidedObject(std::shared_ptr<GameObject>& collideObject);

		void AddOnCollisionBeginEvent(const std::function<void(GameObject& self, GameObject& other)>& collisionFunction);
		void AddOnCollisionStayEvent(const std::function<void(GameObject& self, GameObject& other)>& collisionFunction);
		void AddOnCollisionEndEvent(const std::function<void(GameObject& self, GameObject& other)>& collisionFunction);

		MulticastDelegate <std::string, std::string> m_OnCollisionEvent;
		std::shared_ptr<GameObject> m_CollideObject;

		bool m_IsTutorial = false;
	private:

		std::vector<std::function<void(GameObject& self, GameObject& other)>> m_OnCollisionBegin;
		std::vector<std::function<void(GameObject& self, GameObject& other)>> m_OnCollisionStay;
		std::vector<std::function<void(GameObject& self, GameObject& other)>> m_OnCollisionEnd;

		std::vector<GameObject*> m_PossibleCollidedObjects;
		std::unordered_set<GameObject*> m_CollidedObjects;   ///

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