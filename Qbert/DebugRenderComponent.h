#pragma once


#include"Component.h"
#include"SDL.h"
#include<string>


namespace dae
{
	class MapComponent : public Component
	{

	public:

		MapComponent();

	private:
		virtual void BeginPlay() override;
		void  Render() override;
		void  Update() override;


		// Movbe Grid Command 
		//and resolution as well 
		const int m_NumberTilesX = 15;
		const int m_NumberTilesY = 17;
		float m_TileSize = 48.f;
		
	  int MapArray[15][17] = {
	   1, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
	   1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1,
	   1, 3, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1,
	   1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1,
	   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1,
	   1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1,
	   1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1,
	   1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1,
	   1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1,
	   1, 1, 1, 1, 1, 1, 0, 1, 1, 4, 4, 4, 4, 4, 4,
	   1, 1, 1, 1, 1, 1, 0, 1, 1, 4, 1, 1, 1, 4, 4,
	   1, 1, 1, 1, 1, 1, 0, 1, 1, 4, 1, 4, 4, 4, 4,};











		void parseMapFile(const std::string & filename);
		



	};

}