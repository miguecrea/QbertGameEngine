#include "DebugRenderComponent.h"
#include"Renderer.h"
#include"iostream"
#include"RenderComponent.h"
#include"GameObject.h"
#include"SceneManager.h"
#include"Scene.h"
#include"PengoComponent.h"

dae::MapComponent::MapComponent(std::shared_ptr<dae::GameObject> Player):
	m_Pengo{Player}
{



	//this also needs the player so it can react to what it does 


	//ParseMaps


	for (size_t column = 0; column < m_NumberTilesY; column++)
	{
		for (size_t row = 0; row < m_NumberTilesX; row++)
		{
			if (MapArray[row][column] == 0)
			{
				auto DiamondBlockGameObject = std::make_shared<dae::GameObject>();
				auto DiamondBlockRenderer = std::make_shared<dae::RenderComponent>(-2, false);
				DiamondBlockRenderer->SetTexture("DiamondBlock.png");
				DiamondBlockRenderer->SetDimension(3.f);       //was 0.5     
				DiamondBlockGameObject->AddComponent(DiamondBlockRenderer);
				DiamondBlockGameObject->SetPosition(column * m_TileSize, row * m_TileSize);
				SceneManager::GetInstance().GetCurrentScene()->Add(DiamondBlockGameObject);

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
		PengoComponent->m_OnPengoBreakOrMove.Add(std::bind(&MapComponent::PengoAttackResponse, this));
		

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
			Renderer::GetInstance().DrawSquare(0.f + m_TileSize * X, 0.f + m_TileSize * Y, m_TileSize, SDL_Color{ 55,0,0,255 });

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

void dae::MapComponent::PengoAttackResponse()
{
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




	std::cout << "Hello From Map Class\n";
}
