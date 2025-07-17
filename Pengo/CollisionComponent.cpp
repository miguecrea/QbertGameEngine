#include "CollisionComponent.h"
#include "CollisionComponent.h"
#include "CollisionComponent.h"
#include"GameObject.h"
#include"RectangleComponent.h"
#include<iostream>
#include"RenderComponent.h"
#include"SceneManager.h"
#include"Scene.h"
#include"Audio.h"
#include"staticHeader.h"
#include"SkipLevelsCommand.h"
#include"AddInput.h"
#include"RenderComponent.h"
#include"JumpAnimationComponent.h"
#include"TagComponent.h"
#include"Tags.h"


dae::CollisionComponent::CollisionComponent(std::vector<std::shared_ptr<dae::GameObject>> & enemiesandMap, int dificulty, std::vector<std::shared_ptr<dae::GameObject>>& enemies) :
	m_Map{ enemiesandMap }, m_dificulty{ dificulty }, m_Enemies{ enemies }
{
	InitializeMap();
}

void dae::CollisionComponent::InitializeMap()
{
	switch (m_dificulty)
	{

	case 1:

		m_dificultyEnum = WhichDificulty::Dificulty1;
		break;

	case 2:

		m_dificultyEnum = WhichDificulty::Dificulty2;

		for (int i = 0; i < m_Map.size(); i++)
		{
			m_Map[i]->GetComponent<dae::RenderComponent>()->m_state = 3;    //changes the texture 
		}
		break;
	case 3:

		m_dificultyEnum = WhichDificulty::Dificulty3;

		for (int i = 0; i < m_Map.size(); i++)
		{
			m_Map[i]->GetComponent<dae::RenderComponent>()->m_state = 3;

		}
		break;

	default:
		break;
	}
}

dae::CollisionComponent::~CollisionComponent()
{
}

void dae::CollisionComponent::BeginPlay()
{


}
void dae::CollisionComponent::Render()
{
}

void dae::CollisionComponent::Update()
{
	SDL_Rect selfRect = this->GetOwner()->GetComponent<dae::RectangleComponent>()->GetRect();
	SDL_Rect CollsionWithdEnmiesRect = this->GetOwner()->GetComponent<dae::RectangleComponent>()->GetRectEnemiesCollsion();

	auto tagComponent = this->GetOwner()->GetComponent<dae::TagComponent>();

	if (tagComponent)
	{
		if (tagComponent->GetTag() != SNAKE_PLAYER)  //not snake so Player 
		{
			CheckCollision(selfRect);
		}
	}

	for (int i = 0; i < m_Enemies.size(); i++)
	{
		if (!m_hasCollidedWithEnemies && !m_Isfalling)
		{
			if (Collides(CollsionWithdEnmiesRect, m_Enemies[i]->GetComponent<dae::RectangleComponent>()->GetRect()))
			{
				m_hasCollidedWithEnemies = true;
				this->GetOwner()->SetPosition(this->GetOwner()->GetSavedPosition().x, this->GetOwner()->GetSavedPosition().y);
				this->GetOwner()->GetComponent<dae::JumpAnimationComponent>()->Reset();
				s_CanUseInput = false;
				s_Lives--;
				m_startTimer = true;
				dae::SoundSystem& audio{ dae::Audio::Get() };
				audio.Play(S_PengoDeath, 0.5f, 1);

			}

		}
	}

	// Handle the timer for restarting
	if (m_startTimer)
	{
		m_TimerUntilRestarting += SceneManager::GetInstance().GetDeltaTime();

		if (m_TimerUntilRestarting >= MAX_TIME_UNTIL_RESTARTING)
		{
			s_CanUseInput = true;
			m_TimerUntilRestarting = 0;
			m_startTimer = false;
			m_hasCollidedWithEnemies = false;
		}
	}

	ChangeScene();

	if (s_Lives < 1 && !IsSameScene("ScoresScene"))
	{
		OpenScene(INPUT_NAME_SCENE);
	}

}

void dae::CollisionComponent::CheckCollision(SDL_Rect& selfRect)
{
	for (int i = 0; i < m_Map.size(); i++)
	{
		if (!m_Isfalling)
		{
			if (m_dificulty == 1)
			{
				Dificulty1(selfRect, i);
				m_cubeIndex = 1;
			}
			else if (m_dificulty == 2)
			{
				Dificulty2(selfRect, i);
				m_cubeIndex = 5;
			}
			else
			{
				Dificulty3(selfRect, i);
				m_cubeIndex = 4;
			}
		}
	}
}

void dae::CollisionComponent::ChangeScene()
{
	if (IsSameScene("Level3") || IsSameScene("CoOpScene") || IsSameScene("VersusMode"))
	{

		if (HasLevelBeenComplete(m_cubeIndex))
		{

			OpenScene("InputNameScene");

		}

	}

	if (IsSameScene("level1tutorial"))
	{
		if (HasLevelBeenComplete(m_cubeIndex))
		{
			OpenScene("SinglePlayerScene");
		}

	}
	else if (IsSameScene("SinglePlayerScene"))
	{
		if (HasLevelBeenComplete(m_cubeIndex))
		{
			OpenScene("level2tutorial");
		}

	}

	else if (IsSameScene("level2tutorial"))
	{
		if (HasLevelBeenComplete(m_cubeIndex))
		{
			OpenScene("Level2");
		}

	}
	else if (IsSameScene("Level2"))
	{
		if (HasLevelBeenComplete(m_cubeIndex))
		{
			OpenScene("level3tutorial");


		}

	}


	else if (IsSameScene("level3tutorial"))
	{
		if (HasLevelBeenComplete(m_cubeIndex))
		{
			OpenScene("Level3");


		}


	}





}

void dae::CollisionComponent::Dificulty1(SDL_Rect& selfRect, int i)
{
	if (Collides(selfRect, m_Map[i]->GetComponent<dae::RectangleComponent>()->GetRect()))
	{
		m_Map[i]->GetComponent<dae::RenderComponent>()->m_state = 1;
		if (m_Map[i]->GetComponent<dae::RectangleComponent>()->m_CanAddScore == true)
		{
			s_Score += m_ScoreAdded;
			m_Map[i]->GetComponent<dae::RectangleComponent>()->m_CanAddScore = false;
		}
	}
}

void dae::CollisionComponent::Dificulty2(SDL_Rect& selfRect, int i)
{
	if (Collides(selfRect, m_Map[i]->GetComponent<dae::RectangleComponent>()->GetRect()))
	{
		if (m_Map[i]->GetComponent<dae::RenderComponent>()->m_CanCollide)
		{
			if (m_Map[i]->GetComponent<dae::RenderComponent>()->m_state != 5)  
			{
				m_Map[i]->GetComponent<dae::RenderComponent>()->m_state++;
				s_Score += m_ScoreAddedLevel2;
			}
		}
		m_Map[i]->GetComponent<dae::RenderComponent>()->m_CanCollide = false;
	}

	else
	{
		m_Map[i]->GetComponent<dae::RenderComponent>()->m_CanCollide = true;
	}
}

void dae::CollisionComponent::Dificulty3(SDL_Rect& selfRect, int i)
{

	if (Collides(selfRect, m_Map[i]->GetComponent<dae::RectangleComponent>()->GetRect()))
	{
		if (m_Map[i]->GetComponent<dae::RenderComponent>()->m_CanCollide)
		{
			int & state = m_Map[i]->GetComponent<dae::RenderComponent>()->m_state;

			if (state == 4)
			{
				state--;
			}
			else
			{
				state++;
				s_Score += m_ScoreAddedLevel3;
			}
		}

		m_Map[i]->GetComponent<dae::RenderComponent>()->m_CanCollide = false;
	}
	else
	{
		m_Map[i]->GetComponent<dae::RenderComponent>()->m_CanCollide = true;

	}

}

void dae::CollisionComponent::SetFallingVariable(bool isFalling)
{

	m_Isfalling = isFalling;
}

bool dae::CollisionComponent::IsFalling()
{
	return m_Isfalling;
}

bool dae::CollisionComponent::HasLevelBeenComplete(int index)
{

	for (int i = 0; i < m_Map.size(); i++)
	{
		if (m_Map[i]->GetComponent<dae::RenderComponent>()->m_state != index)
		{
			return false;
		}
	}
	return true;

}

bool dae::CollisionComponent::IsSameScene(const std::string & scenename)
{

	if (SceneManager::GetInstance().GetCurrentScene()->GetName() == scenename)
	{
		return true;
	}
	return false;
}

void  dae::CollisionComponent::OpenScene(const std::string& scenename)
{
	SkipLevelsCommand::m_index++;
	SceneManager::GetInstance().SetCurrentScene(scenename);

	auto& input = InputManager::GetInstance();
	input.ClearSpecificControllerAndKeyboard();

	auto newScene = SceneManager::GetInstance().GetCurrentScene();
	dae::SoundSystem& audio{ dae::Audio::Get() };
	audio.Play(S_EnemyDead, 0.5f, 1);

	if (newScene->GetName() == INPUT_NAME_SCENE)  return;

	auto render = newScene->m_player->GetComponent<dae::RenderComponent>();
	AddControllerKeyboardPlayer1(newScene->m_player, render);

}


bool dae::CollisionComponent::Collides(const SDL_Rect& self, const SDL_Rect& objects)
{
	if (self.x + self.w < objects.x || objects.x + objects.w < self.x)
		return false;

	if (self.x > objects.x + objects.w || objects.x > self.x + self.w)
		return false;

	if (self.y + self.h < objects.y || objects.y + objects.h < self.y)
		return false;

	if (self.y > objects.y + objects.h || objects.y > self.y + self.h)
		return false;

	return true;
}

