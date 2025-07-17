#pragma once


#include "Component.h"
#include<memory>
#include"SDL.h"

namespace dae
{
	class GameObject;

	class FreeFallComponent final : public Component
	{
	public:
		FreeFallComponent();
		virtual ~FreeFallComponent() = default;
		FreeFallComponent(const FreeFallComponent& other) = default;
		FreeFallComponent(FreeFallComponent&& other) = default;
		FreeFallComponent& operator=(const FreeFallComponent& other) = default;
		FreeFallComponent& operator=(FreeFallComponent&& other) = default;

		void  Update() override;
		void  Render() override;
		void SetActive(bool value);
		void SetUnactive();
		bool IsFalling();

	private:

		bool m_IsActive = false;
		GameObject* m_pGameObject;
		const float GRAVITY = -168.f;
		const float INITIAL_VELOCITY_Y = 0.0f; 
		float m_VelocityY = INITIAL_VELOCITY_Y;
		float m_deltaTime = 0;

	};
}