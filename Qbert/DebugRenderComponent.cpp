#include "DebugRenderComponent.h"
#include"Renderer.h"
#include"iostream"
#include"RenderComponent.h"
#include"GameObject.h"
#include"SceneManager.h"
#include"Scene.h"
#include"PengoComponent.h"
#include"TileComponent.h"
#include"TileStaticHelper.h"
#include"GameObject.h"
#include"RenderComponent.h"
#include"Audio.h"
#include"staticHeader.h"

#define BLOCK 9
#define COLLISION 8
#define FREE 0

dae::MapComponent::MapComponent(std::shared_ptr<dae::GameObject> Player) :
	m_Pengo{ Player }
{



	//this also needs the player so it can react to what it does 


	//ParseMaps


	//0 is where tiles will be cant collide 

	//fix the layout 
	//array so we dont committ a mistake 

//	std::cout << MapArray[1][14] << "\n"<<"Index at that Pos\n";


	for (size_t y = 0; y < m_NumberTilesY; ++y)
	{
		for (size_t x = 0; x < m_NumberTilesX; ++x)
		{
			if (MapArray[y][x] == BLOCK)
			{
				auto DiamondBlockGameObject = std::make_shared<dae::GameObject>();
				auto DiamondBlockRenderer = std::make_shared<dae::RenderComponent>(-2, false);
				auto TileComponent = std::make_shared<dae::TileComponent>();
				DiamondBlockRenderer->SetTexture("DiamondBlock.png");
				DiamondBlockRenderer->SetDimension(3.f);
				DiamondBlockGameObject->AddComponent(DiamondBlockRenderer);
				DiamondBlockGameObject->AddComponent(TileComponent);

				DiamondBlockGameObject->SetPosition(x * m_TileSize, y * m_TileSize);

				SceneManager::GetInstance().GetCurrentScene()->Add(DiamondBlockGameObject);
				m_TileObjects[y][x] = DiamondBlockGameObject;
			}
		}
	}

	//add to a vector of game obejcts 


}
void dae::MapComponent::BeginPlay()
{
	if (!m_Pengo)
	{
		std::cout << "Error\n";
		return;
	}
	auto PengoComponent = m_Pengo->GetComponent<dae::PengoComponent>();
	if (PengoComponent)
	{

		using namespace std::placeholders;
		PengoComponent->m_OnPengoBreakOrMove.Add(std::bind(&MapComponent::PengoAttackResponse, this, _1, _2, _3));

	}

}

void dae::MapComponent::Render()
{


	for (size_t Y = 0; Y < m_NumberTilesY; Y++)
	{
		for (size_t X = 0; X < m_NumberTilesX; X++)
		{
			//Renderer::GetInstance().FillSquare(0.f + m_TileSize * X, 0.f + m_TileSize * Y, m_TileSize, SDL_Color{ 255,255,255,250});
			Renderer::GetInstance().DrawSquare(0.f + m_TileSize * X, 0.f + m_TileSize * Y, m_TileSize, SDL_Color{ 255,255,255,250 });

		}
	}
}

void dae::MapComponent::Update()
{



}

void dae::MapComponent::parseMapFile(const std::string& filename)
{



	//std::ifstream file(filename);
	//std::string line;
	//int row = 0;

	//while (std::getline(file, line) && row < 36) { // Read each line of the file
	//	std::istringstream iss(line);
	//	std::string token;
	//	int col = 0;

	//	while (std::getline(iss, token, ',')) { // Tokenize each line by comma
	//		MapArray2[row][col++] = std::stoi(token); // Convert token to int and fill MapArray2
	//	}

	//	row++;
	//}

}

void dae::MapComponent::PengoAttackResponse(Direction PengoDirection, int currenRow, int currentColumn)
{

	//std::cout << currenRow << " " << currentColumn << "\n";

	int TilesToChekc{ 1 };

	auto HasBlockInFrontOneCube = HasABlockInFront(PengoDirection, currenRow, currentColumn, TilesToChekc, BLOCK);
	if (!HasBlockInFrontOneCube.m_hasSomething)
	{
		std::cout << "No block In front\n";
	}
	else
	{
		std::cout << "Has Block In front\n";
		TilesToChekc = 2;


		auto HasBlockInFrontTwoCubes = HasABlockInFront(PengoDirection, currenRow, currentColumn, TilesToChekc, BLOCK);
		auto IsThereWallTwoSpacesAway = HasABlockInFront(PengoDirection, currenRow, currentColumn, TilesToChekc,COLLISION);

		// 
		if (HasBlockInFrontTwoCubes.m_hasSomething || IsThereWallTwoSpacesAway.m_hasSomething)  // 2 blocks away there is something 
		{

			if (m_TileObjects[HasBlockInFrontTwoCubes.row][HasBlockInFrontTwoCubes.column] || IsThereWallTwoSpacesAway.m_hasSomething)
			{
				//break one in front 
				if (m_TileObjects[HasBlockInFrontOneCube.row][HasBlockInFrontOneCube.column])
				{
					auto object = m_TileObjects[HasBlockInFrontOneCube.row][HasBlockInFrontOneCube.column];

					if (object)
					{
						//Destroy the object 
						//delete the object  from array 
						//update the map 
						//destroy if cube is also a wall 
						dae::SoundSystem& audio{ dae::Audio::Get() };
						audio.Play(s_IceBlockDestroyed, 1.f, 0);
						object->GetComponent<dae::RenderComponent>()->SwapVisibility();
						m_TileObjects[HasBlockInFrontOneCube.row][HasBlockInFrontOneCube.column].reset();
						MapArray[HasBlockInFrontOneCube.row][HasBlockInFrontOneCube.column] = FREE;
						std::cout << MapArray[HasBlockInFrontOneCube.row][HasBlockInFrontOneCube.column] << "\n";

					}
					else
					{

					}



				}
			}
		}

		else  
		{    // block in front but not behind it 

			

			TileInfo NextOccupiedTile{};
			TileInfo NextFoundCollision{};
			do
			{
				TilesToChekc++;
				NextOccupiedTile = HasABlockInFront(PengoDirection, currenRow, currentColumn, TilesToChekc,BLOCK);
				NextFoundCollision = HasABlockInFront(PengoDirection, currenRow, currentColumn, TilesToChekc,COLLISION);

			} while (!NextOccupiedTile.m_hasSomething && !NextFoundCollision.m_hasSomething);



			auto TileInFrontTileComponent = m_TileObjects[HasBlockInFrontOneCube.row][HasBlockInFrontOneCube.column]->GetComponent<dae::TileComponent>();
				

			int DesiredRow{};
			int DesiredColumn{};

			if (NextOccupiedTile.m_hasSomething)  //maybe chnage this later 
			{
				if (TileInFrontTileComponent)
				{
			       std::cout << NextOccupiedTile.row << " " << NextOccupiedTile.column << "\n";

					ReturnDesired(DesiredRow, DesiredColumn, NextOccupiedTile);

			      std::cout << DesiredRow << " " << DesiredColumn << "\n";
				
					TileInFrontTileComponent->m_DesiredRow = DesiredRow;
					TileInFrontTileComponent->m_DesiredColumn = DesiredColumn;


					MapArray[HasBlockInFrontOneCube.row][HasBlockInFrontOneCube.column] = FREE;
					MapArray[DesiredRow][DesiredColumn] = BLOCK;  //Other it has to be COLLISION


					m_TileObjects[DesiredRow][DesiredColumn] = m_TileObjects[HasBlockInFrontOneCube.row][HasBlockInFrontOneCube.column];

					m_TileObjects[HasBlockInFrontOneCube.row][HasBlockInFrontOneCube.column].reset();

					TileInFrontTileComponent->SetActive(PengoDirection);

					dae::SoundSystem& audio{ dae::Audio::Get() };
					audio.Play(s_PushedBlockSound, 1.f, 0);

				}

			}
			else
			{
				if (TileInFrontTileComponent)
				{
					dae::SoundSystem& audio{ dae::Audio::Get() };
					audio.Play(s_PushedBlockSound, 1.f, 0);

					std::cout << NextFoundCollision.row << " " << NextFoundCollision.column << "\n";
					
					ReturnDesired(DesiredRow, DesiredColumn, NextFoundCollision);
					std::cout << DesiredRow << " " << DesiredColumn << "\n";


					TileInFrontTileComponent->m_DesiredRow = DesiredRow;
					TileInFrontTileComponent->m_DesiredColumn = DesiredColumn;


					MapArray[HasBlockInFrontOneCube.row][HasBlockInFrontOneCube.column] = FREE;
					MapArray[DesiredRow][DesiredColumn] = BLOCK;  //Other it has to be COLLISION

					m_TileObjects[DesiredRow][DesiredColumn] = m_TileObjects[HasBlockInFrontOneCube.row][HasBlockInFrontOneCube.column];

					m_TileObjects[HasBlockInFrontOneCube.row][HasBlockInFrontOneCube.column].reset();


					TileInFrontTileComponent->SetActive(PengoDirection);

				}


			}

		}

	}

	std::cout << "\n\n\n";

}


dae::TileInfo dae::MapComponent::HasABlockInFront(Direction PengoDirection, int row, int column, int numberTilesToCheck,int TypeOBlock)
{

	TileInfo TileInfo{};

	TileInfo.direction = PengoDirection;
	int rowToCheck{};
	int columnToCheck{};

	switch (PengoDirection)
	{
	case Direction::UP:

		if (MapArray[row - numberTilesToCheck][column] == TypeOBlock)
		{
			rowToCheck = row - numberTilesToCheck;
			columnToCheck = column;
			TileInfo.row = rowToCheck;
			TileInfo.column = columnToCheck;
			TileInfo.m_hasSomething = true;
		}


		std::cout << "up\n";
		return TileInfo;

		break;
	case Direction::DOWN:

		if (MapArray[row + numberTilesToCheck][column] == TypeOBlock)
		{

			rowToCheck = row + numberTilesToCheck;
			columnToCheck = column;

			TileInfo.row = rowToCheck;
			TileInfo.column = columnToCheck;
			TileInfo.m_hasSomething = true;
		}


		std::cout << "down\n";
		return TileInfo;


		break;
	case Direction::LEFT:

		if (MapArray[row][column - numberTilesToCheck] == TypeOBlock)
		{

			rowToCheck = row;
			columnToCheck = column - numberTilesToCheck;

			TileInfo.row = rowToCheck;
			TileInfo.column = columnToCheck;
			TileInfo.m_hasSomething = true;
		}



		std::cout << "left\n";

		return TileInfo;


		break;
	case Direction::RIGHT:


		if (MapArray[row][column + numberTilesToCheck] == TypeOBlock)
		{

			rowToCheck = row;
			columnToCheck = column + numberTilesToCheck;

			TileInfo.row = rowToCheck;
			TileInfo.column = columnToCheck;
			TileInfo.m_hasSomething = true;
		}
		std::cout << "right\n";

		return TileInfo;

		break;
	default:
		break;
	}

}

bool dae::MapComponent::IsCubeCollision(Direction PengoDirection, int row, int column, int numberTilesToCheck)
{

	switch (PengoDirection)
	{
	case Direction::UP:

		if (MapArray[row - numberTilesToCheck][column] == COLLISION)
		{
			return true;
		}

		return false;

		break;
	case Direction::DOWN:

		if (MapArray[row + numberTilesToCheck][column] == COLLISION)
		{
			return true;
		}

		return false;

		break;
	case Direction::LEFT:

		if (MapArray[row][column - numberTilesToCheck] == COLLISION)
		{

			return true;
		}
		return false;


		break;
	case Direction::RIGHT:


		if (MapArray[row][column + numberTilesToCheck] == COLLISION)
		{
			return true;

		}
		return false;

		break;
	default:
		break;
	}
}

bool dae::MapComponent::HasBlockIn(int row, int column)
{
	return false;
}

void dae::MapComponent::ReturnDesired(int & row, int & column, const TileInfo & Tile)
{

	row = Tile.row;
	column = Tile.column;

	switch (Tile.direction)
	{
	case Direction::UP:             

		row += 1;
		

		break;
	case Direction::DOWN:

		row -= 1;

		break;
	case Direction::LEFT:

	
		column += 1;


		break;
	case Direction::RIGHT:

		column -= 1;
		break;
	default:
		break;
	}
	
}


