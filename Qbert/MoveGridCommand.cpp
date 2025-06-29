#include "MoveGridCommand.h"
#include"iostream"
#include"GameObject.h"
#include"SceneManager.h"


dae::MoveGridCommand::MoveGridCommand(std::shared_ptr<dae::GameObject> pGameObject):
	m_pGameObject{pGameObject}

{

}

dae::MoveGridCommand::MoveGridCommand()
{
}

void dae::MoveGridCommand::Execute()
{


	// handle movement event 





	if (abs(m_Value.x) > abs(m_Value.y))  // Prioritize horizontal
	{
		m_Direction = { (m_Value.x > 0.f ? 1.f : -1.f), 0.f,0.f};
	}
	else  // Prioritize vertical
	{
		m_Direction = { 0.f, (m_Value.y > 0.f ? 1.f : -1.f),0.0f};
	}
	glm::vec3 newPosition = m_pGameObject->GetWorldPosition() + m_Direction * SceneManager::GetInstance().GetDeltaTime() * moveSpeed;

	//int column = static_cast<int>(std::floor(newPosition.x / tileSize));
	//int row = static_cast<int>(std::floor(newPosition.y / tileSize));


	//glm::vec3 snappedPosition{ column * tileSize, row * tileSize, 0.f };

	//std::cout << snappedPosition.x << " " << snappedPosition.y << "\n";

	m_pGameObject->SetPosition(newPosition.x, newPosition.y);


	
	

	
	//get needs the map game object as well as parameters 

	//first make  it move left right ,up and down
	// //save the direction it is looking at 
	// snap to grid 
	// make sure it wont hit anything all rhe other blocks 
	// 
	//then we 

	//when we hit a block game object broadcast commands //and maps uddates etc 
	//hit and break block

	std::cout << "ggasdasdas\n";


}
