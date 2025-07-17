#pragma once


#include"Component.h"
#include"memory"
#include"PengoDirection.h"
#include"DelegateBase.h"
namespace dae
{

	class RenderComponent;
	class GameObject;
	class RectangleComponent;
	class MapComponent;
	class TileComponent : public Component
	{

	public:

		MulticastDelegate<float, float> m_BlockHatched;
		TileComponent();
		int m_DesiredRow = 0;
		int m_DesiredColumn = 0;

		int m_CurrentRow = 0;
		int m_CurrentColumn = 0;

		void SetActive(Direction direction);
		Direction m_Direction;

		void SetMap(MapComponent *  Map);

		bool m_IsNest = false;
		bool m_Destroyed = false;
	private:
		MapComponent * m_Map;
		virtual void BeginPlay() override;
		void  Render() override;
		void  Update() override;
		bool m_StartMoving = false;
		float m_MovementSpeed = 240.f;
		
		float halfWidth{};
		float halfHeight{};
		float m_TileSize = 48.f;

		std::shared_ptr<dae::RenderComponent> m_renderComponent;
		std::shared_ptr<dae::RectangleComponent> m_RectangleComponent;

		float m_Timer = 0.f;
		float m_SecondsUntilSpawning = 0.f;
		float RandomFloatStep1(float min, float max);

		float m_MinSeconds = 8.f;
		float m_MaxSeconds = 20.f;
		

		float m_TimerForchanging = 0.f;

		void ToogleSprite();



	};

}