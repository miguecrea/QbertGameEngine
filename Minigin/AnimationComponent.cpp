#include "AnimationComponent.h"



dae::AnimationComponent::AnimationComponent(std::shared_ptr<Texture2D> Texture, int NrROws, int NRColumns, int MaxNumberFrames, int framesPerSecond, Type AnimationType, int currentFrame, int WhichColumn):
	 m_pTexture {Texture}
	,m_Rows { NrROws }
	, m_Columns{ NRColumns }
	, m_MaxNumberFrames{ MaxNumberFrames }
	, m_FramesPerSecond{ framesPerSecond }
	, m_TypeOfAnimation{ AnimationType }
	, m_CurrentFrame{ currentFrame }
	, m_WhichColumns{ WhichColumn }
	, m_IsAnimationPlaying{ false }
	, m_TotalTimeElapsed{ 0 }
	, m_copy{ currentFrame }

{
}

void dae::AnimationComponent::Draw(float x ,float y,float scale)  
{

	    const int FRAME_WIDTH{ GetFrameWidth() };
		const int FRAME_HEIGTH{ GetFrameHeight() };

		SDL_Rect SourceRect{};
		

		SourceRect.x = FRAME_WIDTH * m_CurrentFrame;
		SourceRect.y = FRAME_HEIGTH * m_WhichColumns;
		SourceRect.w = FRAME_WIDTH;
		SourceRect.h = FRAME_HEIGTH;
	

		m_destinationRect.x =int(x);
		m_destinationRect.y = int(y);

	
		m_destinationRect.w = static_cast<int>(SourceRect.w * scale);  
		m_destinationRect.h = static_cast<int>(SourceRect.h *scale);

		Renderer::GetInstance().RenderTexture(*m_pTexture, m_destinationRect, SourceRect);

}

void dae::AnimationComponent::Update(float elapsedSec)
{



	switch (m_TypeOfAnimation)
	{
	case Type::loop:

		m_TotalTimeElapsed += elapsedSec;
		if (m_TotalTimeElapsed >= 1.f / m_FramesPerSecond)
		{
			m_TotalTimeElapsed -= 1.f / m_FramesPerSecond;


			m_CurrentFrame++;

			if (m_CurrentFrame % m_MaxNumberFrames == 0)  //this I am not sure 
			{
				m_CurrentFrame = 0;
				m_TotalTimeElapsed = 0;
			}


		}

		break;
	case Type::onlyOnce:

		if (m_IsAnimationPlaying)
		{
			m_TotalTimeElapsed += elapsedSec;

			if (m_TotalTimeElapsed >= 1.f / m_FramesPerSecond)
			{
				m_TotalTimeElapsed -= 1.f / m_FramesPerSecond;


				m_CurrentFrame++;

				if (m_CurrentFrame >= m_MaxNumberFrames)
				{
					m_CurrentFrame = 0;
					m_TotalTimeElapsed = 0;
					m_IsAnimationPlaying = false;

				}

			}

		}
		break;
	case Type::StartAtNoZero:

		m_TotalTimeElapsed += elapsedSec;

		if (m_TotalTimeElapsed >= 1.f / m_FramesPerSecond)
		{
			m_TotalTimeElapsed -= 1.f / m_FramesPerSecond;


			m_CurrentFrame++;

			if (m_CurrentFrame >= m_MaxNumberFrames)
			{

				m_CurrentFrame = m_copy;
				m_TotalTimeElapsed = 0;


			}

		}

		break;

	case Type::OnlyOnceandEndAtLast:

		if (m_IsAnimationPlaying)
		{
			m_TotalTimeElapsed += elapsedSec;

			if (m_TotalTimeElapsed >= 1.f / m_FramesPerSecond)
			{
				m_TotalTimeElapsed -= 1.f / m_FramesPerSecond;

				m_CurrentFrame++;

				if (m_CurrentFrame >= 3)
				{
					m_CurrentFrame = 3;
					m_TotalTimeElapsed = 0;
					m_IsAnimationPlaying = false;

				}
			}
		}
		break;
	default:
		break;
	}


	
}

int dae::AnimationComponent::GetFrameWidth()
{
	return m_pTexture->GetSize().x / m_Columns;
}

int dae::AnimationComponent::GetFrameHeight()
{
	return m_pTexture->GetSize().y / m_Rows;

}

SDL_Rect & dae::AnimationComponent::ReturnShape()
{
	return m_destinationRect;
}
