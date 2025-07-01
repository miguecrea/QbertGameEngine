#pragma once


#include"Component.h"
#include"memory"
namespace dae
{


	class GameObject;
	class TileComponent : public Component
	{

	public:

		TileComponent();

	private:
		virtual void BeginPlay() override;
		void  Render() override;
		void  Update() override;

		int m_DesiredRow = 0;
		int m_DesiredColumn = 0;

		int m_CurrentRow = 0;
		int m_CurrentColumn = 0;



	};

}