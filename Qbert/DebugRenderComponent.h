#pragma once


#include"Component.h"
#include"SDL.h"
#include<string>
#include"memory"
#include"PengoDirection.h"
#include<vector>


namespace dae
{


	class GameObject;
	class MapComponent : public Component
	{

	public:

		MapComponent(std::shared_ptr<dae::GameObject> Player);

	private:
		virtual void BeginPlay() override;
		void  Render() override;
		void  Update() override;

		std::shared_ptr<dae::GameObject> m_Pengo;


		// Movbe Grid Command 
		//and resolution as well 
		const int m_NumberTilesX = 15;
		const int m_NumberTilesY = 17;
		float m_TileSize = 48.f;
		
	
			int MapArray[15][17] = {
			 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7,
			 0, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
			 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
			 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
			 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3,
			 3, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 3,
			 3, 3, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 3,
			 3, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 3,
			 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
			 3, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 3,
			 3, 0, 1, 1, 1, 7, 0, 1, 1, 0, 1, 1, 1, 1, 3,
			 3, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 3,
			 3, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 3,
			 3, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 3,
			 3, 1, 1, 1, 1, 7, 0, 1, 1, 4, 4, 4, 4, 4, 3,
			 3, 1, 1, 1, 1, 1, 0, 1, 1, 4, 1, 1, 1, 4, 3,
			 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,};



		





	


		std::vector<std::shared_ptr<dae::GameObject>> m_TilesVector;

		

		void parseMapFile(const std::string & filename);
		void PengoAttackResponse(Direction PengoDirection, int currenRow, int currentColumn);
		bool HasABlockBehindTheOneInFront(Direction PengoDirection);
		bool HasABlockInFront(Direction PengoDirection,int row,int column,int numberTilesToCheck);
		bool HasBlockIn(int row, int column);

		
	};

}