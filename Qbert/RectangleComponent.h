#pragma once
#include"Component.h"
#include"SDL.h"

namespace dae
{


	class RectangleComponent : public Component
	{

	public:

		RectangleComponent(int width, int height);
		virtual ~RectangleComponent();
		RectangleComponent(const RectangleComponent& other) = default;
		RectangleComponent(RectangleComponent&& other) = default;
		RectangleComponent& operator=(const RectangleComponent& other) = default;
		RectangleComponent& operator=(RectangleComponent&& other) = default;

		virtual void Render() override;
		virtual void Update() override;

		void AddOffset(int x, int y);
		void AddOffsetEnemiesCollidingRect(int x, int y);
		void SetWidthAndHeightCollidingRectangle(int x, int y);

		int	m_offSetX = 0;
		int	m_offSetY = 0;
		int	m_offSetX2 = 0;
		int	m_offSetY2 = 0;

		float m_totalTimeElapsed{};
		SDL_Rect m_Rect = {};
		SDL_Rect m_CollsionWithEnemiesRect = {};

		SDL_Rect & GetRect();
		SDL_Rect & GetRectEnemiesCollsion();

		void SetWidth();
		void SetHeight();
		bool m_CanAddScore = true;

	private:

		float m_WorldScale = 2.f;
	};

}