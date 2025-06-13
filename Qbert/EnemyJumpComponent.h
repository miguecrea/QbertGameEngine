#pragma once

#include"Component.h"
#include<memory>
#include"glm/vec3.hpp"
#include "TypeOfAi.h"
namespace dae
{
	class GameObject;

	class EnemyJumpComponent final : public Component
	{
	public:

		EnemyJumpComponent(float jumpWaitingTime, float TimeUntilDrawing, TypeOfAi AiType, float JumpDuration = 1.4f);    /// vector  //time to update 
		virtual ~EnemyJumpComponent() = default;
		EnemyJumpComponent(const EnemyJumpComponent& other) = default;
		EnemyJumpComponent(EnemyJumpComponent&& other) = default;
		EnemyJumpComponent& operator=(const EnemyJumpComponent& other) = default;
		EnemyJumpComponent& operator=(EnemyJumpComponent&& other) = default;
		void Update() override;
		void Render() override;
		TypeOfAi m_TypeOfAi{};
		void SetActive(bool isActive);
		void Reset();
		void ChangeSnakeDirection();
		float m_posX[5]{ };
		float m_posY[5]{ };
	private:

		GameObject* m_pGameObject = nullptr;
		std::shared_ptr<GameObject> m_CollideObject;
		bool m_IsActive = false;
		float m_TimeUntilActive = 2.f;
		float m_Elapsed = 0.0f;
		const float m_Duration = 1.4f; // Duration of the jump
		const float m_ArcHeight = -10.0f; // Height of the jump
		glm::vec3 m_StartPosition{};
		glm::vec3 m_EndPosition{};
		glm::vec3 m_JumpOffset{ -12,20,0 };

		float m_TimeToUpdate = 2.f;
		float m_TimeToStartUpdatingObject;
		bool m_execute = false;
		bool m_Update = true;
	};
}