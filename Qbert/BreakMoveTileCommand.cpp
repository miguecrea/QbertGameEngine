#include "BreakMoveTileCommand.h"
#include"iostream"
#include"GameObject.h"
#include"PengoComponent.h"
dae::BreakMoveTileCommand::BreakMoveTileCommand(std::shared_ptr<dae::GameObject> pGameObject):
	m_Pengo{pGameObject}
{
}

void dae::BreakMoveTileCommand::Execute()
{


	auto PengoComponent = m_Pengo->GetComponent<dae::PengoComponent>();

	PengoComponent->m_OnPengoBreakOrMove.Broadcast();

	std::cout << "BreakingTile\n";




	//Send event to game manager that has the player
	//and check if the 2 tiles are in the same place


	//break tile that is in front if there are tiules behind


	//move tiles 







}

void dae::BreakMoveTileCommand::Undo()
{
}
