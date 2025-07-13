#pragma once


#include"Component.h"
#include"memory"
#include"PengoDirection.h"
namespace dae
{

	class RenderComponent;
	class GameObject;
	class TileComponent : public Component
	{

	public:

		TileComponent();
		int m_DesiredRow = 0;
		int m_DesiredColumn = 0;

		void SetActive(Direction direction);
		Direction m_Direction;
	private:
		virtual void BeginPlay() override;
		void  Render() override;
		void  Update() override;
		int m_CurrentRow = 0;
		int m_CurrentColumn = 0;
		bool m_StartMoving = false;
		float m_MovementSpeed = 240.f;
		
		float halfWidth{};
		float halfHeight{};
		float m_TileSize = 48.f;

		std::shared_ptr<dae::RenderComponent> m_renderComponent;


	};

}