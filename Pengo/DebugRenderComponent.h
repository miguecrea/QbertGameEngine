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

		
		MapComponent(std::shared_ptr<dae::GameObject> Player,const std::string & mapFileName,int NumberEnemies, std::shared_ptr<dae::GameObject> Player2 = nullptr);
		MulticastDelegate<> m_IncreaseScoreDelegate;
		MulticastDelegate <> m_On3TilesMatched;

		const int MapHeight = 17;
		const int MapWidth = 15;
		int MapArray[17][15];
		std::shared_ptr<dae::GameObject> m_TileObjects[17][15];
		std::vector<TileInfo> m_SpeciaTiles{};
		std::vector<std::shared_ptr<dae::GameObject>> GetTiles();
		std::vector<std::shared_ptr<dae::GameObject>> GetTilesWidthEnmies();
		void SetPlayer2(std::shared_ptr<dae::GameObject> player2);

	private:

		int m_NumberEnemies{};
		std::string m_MapFileName;
		virtual void BeginPlay() override;
		void  Render() override;
		void  Update() override;
		std::shared_ptr<dae::GameObject> m_Pengo;
		std::shared_ptr<dae::GameObject> m_Player2;

		float NumberOfEnemiesNest = 0;
		float MAXNumberOfEnemiesNest = 2;
		const int m_NumberTilesX = 15;
		const int m_NumberTilesY = 17;
		float m_TileSize = 48.f;

		std::vector<std::shared_ptr<dae::GameObject>> m_TilesVector;
		std::vector<std::shared_ptr<dae::GameObject>> m_TilesWidhEnemies;

		int m_especialTilesIndeces[3][3];

		void parseMapFile(const std::string& filename);
		void PengoAttackResponse(Direction PengoDirection, int currenRow, int currentColumn,bool OnlyBreak);
		void DestroyCube(dae::TileInfo& HasBlockInFrontOneCube);
		dae::TileInfo HasABlockInFront(Direction PengoDirection, int row, int column, int numberTilesToCheck,int TypeOBlock);
		bool IsCubeCollision(Direction PengoDirection, int row, int column, int numberTilesToCheck);
		bool HasBlockIn(int row, int column);
		void ReturnDesired(int & row, int & column, const TileInfo& Tile);
		bool  HasThreeAlignedTiles(const std::vector<TileInfo> & tiles);

		bool percentage(int percent);
	};

}