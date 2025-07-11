#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "SceneManager.h"
#include "GameObject.h"



dae::RenderComponent::RenderComponent(int priority, bool useAnimation)
	:Component(priority), m_pTexture{ nullptr }, m_useAnimation{ useAnimation }
{

}



dae::RenderComponent::~RenderComponent()
{

}

void dae::RenderComponent::SetVisibility(bool visible)
{

	m_Visible = visible;
}

void dae::RenderComponent::SwapVisibility()
{
	m_Visible = !m_Visible;
}

bool dae::RenderComponent::IsVisible()
{
	return m_Visible;
}

void dae::RenderComponent::AddToVector(int NrROws, int NRColumns, int MaxNumberFrames, int framesPerSecond, AnimationComponent::Type AnimationType, int currentFrame, int WhichColumn)
{
	m_animationVector.push_back(std::make_unique<AnimationComponent>(m_pTexture, NrROws, NRColumns, MaxNumberFrames, framesPerSecond, AnimationType, currentFrame, WhichColumn));


}
SDL_Rect dae::RenderComponent::ReturnShape()
{
	return SDL_Rect(m_ObjectShape);
}

void dae::RenderComponent::Render()
{
	Draw();
}

void dae::RenderComponent::Draw()
{
	if (m_pTexture)
	{
		glm::vec3 position{ GetOwner()->GetWorldPosition() };

		//position.x *= 2;
		//position.y *= 2;

		m_LastPosition = position;

		if (m_useAnimation)
		{
			if (m_Visible)
			{
				m_animationVector[m_state]->Draw(position.x, position.y, m_scale);

			}
			m_ObjectShape.x = int(position.x);
			m_ObjectShape.y = int(position.y);
			m_ObjectShape.w = m_animationVector[m_state]->GetFrameWidth();
			m_ObjectShape.h = m_animationVector[m_state]->GetFrameHeight();

		}
		else
		{

			if (m_Visible)
			{
			Renderer::GetInstance().RenderTexture(*m_pTexture, position.x, position.y, float(m_pTexture.get()->GetSize().x) * m_scale, float(m_pTexture.get()->GetSize().y) * m_scale);

			}

			m_ObjectShape.x = int(position.x);
			m_ObjectShape.y = int(position.y);
			m_ObjectShape.w = m_pTexture.get()->GetSize().x;
			m_ObjectShape.h = m_pTexture.get()->GetSize().y;

		}

	}
}

void dae::RenderComponent::Update()
{
	if (m_useAnimation)
	{
		m_animationVector[m_state]->Update(SceneManager::GetInstance().GetDeltaTime());
	}
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	m_pTexture = pTexture;
}

void dae::RenderComponent::SetDimension(float scale)  
{
	m_scale = scale;

}

