#pragma once


#include"Component.h"
#include"SDL.h"

namespace dae
{
	class MapComponent : public Component
	{

	public:

		MapComponent() = default;

	private:
		virtual void BeginPlay() override;
		void  Render() override;
		void  Update() override;

		int m_NumberTilesX = 15;
		int m_NumberTilesY = 17;
		float m_TileSize = 48.f;

	};

}