#pragma once


#include"Component.h"
#include"SDL.h"
#include<string>
#include"memory"
#include"PengoDirection.h"
#include<vector>
#include"TileInfo.h"
#include"DelegateBase.h"


namespace dae
{
	class GameObject;
	class MapComponent : public Component
	{

	public:

		
		MapComponent(std::shared_ptr<dae::GameObject> Player);


		 


		//columsn and rows 
		/*static const int COLUMNS = 15;
		static const int ROWS = 17;*/
	
		// rowa 17 columns 15 
		int MapArray[17][15] =
		{
			{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
			{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 8},
			{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 8},
			{8, 0, 0, 0, 0, 0, 9, 0, 9, 0, 0, 0, 0, 9, 8},
			{8, 9, 9, 9, 9, 0, 5, 5, 0, 0, 0, 9, 0, 9, 8},
			{8, 0, 0, 1, 1, 0, 0, 1, 0, 9, 0, 9, 0, 0, 8},
			{8, 9, 9, 9, 9, 0, 0, 0, 9, 9, 0, 9, 0, 0, 8},
			{8, 0, 9, 0, 0, 9, 9, 9, 9, 9, 0, 9, 9, 0, 8},
			{8, 0, 0, 0, 0, 0, 9, 0, 5, 9, 0, 0, 0, 0, 8},
			{8, 0, 9, 9, 0, 9, 0, 0, 0, 9, 0, 0, 0, 0, 8},
			{8, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 8},
			{8, 0, 9, 9, 9, 9, 9, 9, 0, 9, 9, 0, 0, 0, 8},
			{8, 0, 9, 0, 0, 1, 9, 0, 0, 1, 0, 0, 0, 0, 8},
			{8, 0, 9, 0, 0, 1, 9, 0, 0, 0, 0, 0, 0, 0, 8},
			{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 8},
			{8, 9, 9, 0, 9, 0, 0, 0, 9, 0, 0, 0, 0, 9, 8},
			{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
		};

		std::shared_ptr<dae::GameObject> m_TileObjects[17][15];
		std::vector<TileInfo> m_SpeciaTiles{};

		MulticastDelegate <> m_On3TilesMatched;



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

		std::vector<std::shared_ptr<dae::GameObject>> m_TilesVector;
		int m_especialTilesIndeces[3][3];

		void parseMapFile(const std::string& filename);
		void PengoAttackResponse(Direction PengoDirection, int currenRow, int currentColumn);
		void DestroyCube(dae::TileInfo& HasBlockInFrontOneCube);
		dae::TileInfo HasABlockInFront(Direction PengoDirection, int row, int column, int numberTilesToCheck,int TypeOBlock);
		bool IsCubeCollision(Direction PengoDirection, int row, int column, int numberTilesToCheck);
		bool HasBlockIn(int row, int column);


		void ReturnDesired(int & row, int & column, const TileInfo& Tile);
		bool  HasThreeAlignedTiles(const std::vector<TileInfo> & tiles);


	};

}