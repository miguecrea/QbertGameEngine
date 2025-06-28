#include "Command1D.h"

using namespace dae;

Command1D::Command1D()
    : Command{}
{
}

void dae::Command1D::SetValue(float value)
{
    m_Value = value;
}
void dae::Command1D::Execute()
{
}
