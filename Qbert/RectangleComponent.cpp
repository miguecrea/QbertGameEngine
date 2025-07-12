#include "RectangleComponent.h"
#include"GameObject.h"
#include"Renderer.h"

dae::RectangleComponent::RectangleComponent(int width, int height)
{
	m_Rect.w = width;
	m_Rect.h = height;

}

dae::RectangleComponent::~RectangleComponent()
{
}


void dae::RectangleComponent::Update()
{
	m_Rect.x = int(GetOwner()->GetWorldPosition().x + m_offSetX);
	m_Rect.y = int(GetOwner()->GetWorldPosition().y  + m_offSetY);




	m_CollsionWithEnemiesRect.x = int(GetOwner()->GetWorldPosition().x + m_offSetX2);
	m_CollsionWithEnemiesRect.y = int(GetOwner()->GetWorldPosition().y + m_offSetY2);
}

void dae::RectangleComponent::AddOffset(int x, int y)
{
	m_offSetX = x;
	m_offSetY = y;
}

void dae::RectangleComponent::AddOffsetEnemiesCollidingRect(int x, int y)
{
	m_offSetX2 = x;
	m_offSetY2 = y;
}

void dae::RectangleComponent::SetWidthAndHeightCollidingRectangle(int x, int y)
{
	m_CollsionWithEnemiesRect.w = x;
	m_CollsionWithEnemiesRect.h = y;
}

SDL_Rect & dae::RectangleComponent::GetRect()
{
	return m_Rect;
}

SDL_Rect & dae::RectangleComponent::GetRectEnemiesCollsion()
{
	return m_CollsionWithEnemiesRect;
}

void dae::RectangleComponent::SetWidth()
{
}

void dae::RectangleComponent::SetHeight()
{
	m_Rect.h += 20;  
	m_Rect.w += 40;
}

void dae::RectangleComponent::Render()
{
     Renderer::GetInstance().FillSquare(float(m_Rect.x),float( m_Rect.y),float(m_Rect.w),float(m_Rect.h), SDL_Color{ 255,0,0,255 });
	//Renderer::GetInstance().FillSquare(float(m_CollsionWithEnemiesRect.x),float(m_CollsionWithEnemiesRect.y),float(m_CollsionWithEnemiesRect.w),float(m_CollsionWithEnemiesRect.h), SDL_Color{ 255,255,0,255 });
}