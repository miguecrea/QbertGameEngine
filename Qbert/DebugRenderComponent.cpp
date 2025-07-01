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

#define BLOCK 9
#define COLLISION 8

dae::MapComponent::MapComponent(std::shared_ptr<dae::GameObject> Player) :
	m_Pengo{ Player }
{



	//this also needs the player so it can react to what it does 


	//ParseMaps


	//0 is where tiles will be cant collide 

	for (size_t row = 0; row < m_NumberTilesY; row++)
	{
		for (size_t column = 0; column < m_NumberTilesX; column++)
		{

			if (MapArray[row][column] == BLOCK)
			{

				auto DiamondBlockGameObject = std::make_shared<dae::GameObject>();
				auto DiamondBlockRenderer = std::make_shared<dae::RenderComponent>(-2, false);
				auto TileComponent = std::make_shared<dae::TileComponent>();
				DiamondBlockRenderer->SetTexture("DiamondBlock.png");
				DiamondBlockRenderer->SetDimension(3.f);       //was 0.5     
				DiamondBlockGameObject->AddComponent(DiamondBlockRenderer);
				DiamondBlockGameObject->AddComponent(TileComponent);
				DiamondBlockGameObject->SetPosition(column * m_TileSize, row * m_TileSize);
				SceneManager::GetInstance().GetCurrentScene()->Add(DiamondBlockGameObject);

				//save 

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
	/*Renderer::GetInstance().FillSquare(100.f, 100.f, 100.f, 100.f, SDL_Color{
		55,0,0,255 });*/


		//create inside or outside 

		//takes a series of game objects the tiles and Sets the pos

		//move tile to another tile when new Tile 
		//check in the update if cuurent is desired tiles id that stop moving and update 




		//parsear el mapa 
		//cambiatr el color y que no se pueda 

	for (size_t Y = 0; Y < m_NumberTilesY; Y++)
	{
		for (size_t X = 0; X < m_NumberTilesX; X++)
		{
			//Renderer::GetInstance().FillSquare(0.f + m_TileSize * X, 0.f + m_TileSize * Y, m_TileSize, SDL_Color{ 255,255,255,250});
			Renderer::GetInstance().DrawSquare(0.f + m_TileSize * X, 0.f + m_TileSize * Y, m_TileSize, SDL_Color{ 255,255,255,250});

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

	std::cout << currenRow << " " << currentColumn << "\n";


	//make sure index does not go out of scope 
	//I am Checking if it is a number that can go wrong use an enum or somethinf o
	//la pred is ann issue as wrell 


	int TilesToChekc{ 1 };
	if (!HasABlockInFront(PengoDirection, currenRow, currentColumn,TilesToChekc))
	{
		std::cout << "No block In front\n";
	}
	else
	{
		//I have a block in front 

		if (HasABlockInFront(PengoDirection, currenRow, currentColumn, 2))
		{
			//Update map 
			//destroy block on that Position


			std::cout << " destroying first Block \n";

			//block destroy the previous one 
		}
		else
		{
			std::cout << "Moving Block\n";

			//keep on checking //move until finds either collision or another block 

		}



	}
	
	std::cout << "\n\n\n";












	//calculate the tile behind the one in front is empty or not //and also if it is valid

   //tile component 

   //stop rendering
   //stop collision
   //set map to can walk normally again 





	//HasABlockBehindTheOneInFront(PengoDirection);

	//	TileStaticHelper::GetInstance().TestFunction();

		//if(does not have Tile In after that one)
		//{
		//

		//get tile on that Position
		//move and update the map 







		 //}
		 //else
		//{
			   //break;
		//}



		//current ro and column are wrong

		//have to break the block in case 

		// Prameters player row and columns 
		//and direction 

		//check if the special tiles ,make a variable is special 
		//ar moved if they are moved 
		//make event from here 



		//check if there is a tile behind the ine in the direction
		//it is looking 
		//if there is break it if not 
		// Call Move on the tile
		//and update thye map 




}

bool dae::MapComponent::HasABlockBehindTheOneInFront(Direction PengoDirection)
{
	//switch (PengoDirection)
	//{
	//case Direction::UP:
	//	map.MapArray[][]
	//	std::cout << "Up\n";

	//	break;
	//case Direction::DOWN:
	//	std::cout << "down\n";

	//	break;
	//case Direction::LEFT:
	//	std::cout << "left\n";

	//	//map.MapArray[]

	//	break;
	//case Direction::RIGHT:

	//	std::cout << "right\n";
	//	break;
	//default:
	//	break;
	//}

	return true;
}

bool dae::MapComponent::HasABlockInFront(Direction PengoDirection, int row, int column,int numberTilesToCheck)
{


	switch (PengoDirection)
	{
	case Direction::UP:

		if (MapArray[row - numberTilesToCheck][column] == BLOCK)
		{
			return true;
		}

		std::cout << "Up\n";


		return false;



		break;
	case Direction::DOWN:

		if (MapArray[row  + numberTilesToCheck][column] == BLOCK)
		{
			return true;
		}

		std::cout << "down\n";


		return false;


		break;
	case Direction::LEFT:

		if (MapArray[row][column - numberTilesToCheck] == BLOCK)
		{
			return true;
		}


		std::cout << "left\n";

		return false;


		break;
	case Direction::RIGHT:


		if (MapArray[row][column + numberTilesToCheck] == BLOCK)
		{
			return true;
		}
		std::cout << "right\n";

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
