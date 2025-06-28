#include "Command2D.h"


using namespace dae;

void dae::Command2D::SetValue(const glm::vec2& value)
{
    m_Value = value;
}

void dae::Command2D::Execute()
{
}


void dae::Command2D::Undo()
{
}


