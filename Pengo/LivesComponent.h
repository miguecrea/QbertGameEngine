#pragma once
#include "Component.h"
#include <string>
#include"memory"

namespace dae
{
	class GameObject;
	class TextComponent;
	class PlayerComponent;
	class InputManager;
	class Scene;

	class LivesComponent final : public Component
	{
	public:


		LivesComponent();
		virtual ~LivesComponent();
		LivesComponent(const LivesComponent& other) = default;
		LivesComponent(LivesComponent&& other) = default;
		LivesComponent& operator=(const LivesComponent& other) = default;
		LivesComponent& operator=(LivesComponent&& other) = default;

		virtual void BeginPlay();
		virtual void Render();
		virtual void Update() override;

		void DecreaseLive();
		void AddInputNameKeyBinds(InputManager & input,Scene* scene);
		bool m_PlayBackGroundMusic = false;
		float m_Timer = 0.f;
		bool m_StartTimer = false;

	private:
	};
}


