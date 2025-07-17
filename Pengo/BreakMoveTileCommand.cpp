#include "BreakMoveTileCommand.h"
#include"iostream"
#include"GameObject.h"
#include"PengoComponent.h"
#include"TileStaticHelper.h"

dae::BreakMoveTileCommand::BreakMoveTileCommand(std::shared_ptr<dae::GameObject> pGameObject, bool OnlyBreak):
	m_Pengo{pGameObject},m_OnlyBreak{OnlyBreak}
{
	if (m_Pengo)
	{
	m_PengoComponent = m_Pengo->GetComponent<dae::PengoComponent>();

	}
	else
	{
		std::cout << "Error Pengo Game Object is null\n";
	}
}

void dae::BreakMoveTileCommand::Execute()
{
	int row  = TileStaticHelper::GetInstance().GetRow(m_Pengo->GetWorldPosition().y);
	int Column = TileStaticHelper::GetInstance().GetColumn(m_Pengo->GetWorldPosition().x);
	if (m_PengoComponent)
	{
		//
		m_PengoComponent->m_OnPengoBreakOrMove.Broadcast(m_PengoComponent->m_CurrentDirection,row,Column,m_OnlyBreak);
	}
}

void dae::BreakMoveTileCommand::Undo()
{
}
