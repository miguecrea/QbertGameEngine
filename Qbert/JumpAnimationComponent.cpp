#include "JumpAnimationComponent.h"
#include"GameObject.h"
#include"SceneManager.h"
#include <glm/gtc/constants.hpp> // For glm::pi<float>()
#include"SceneManager.h"
#include"glm/vec3.hpp"
#include"Renderer.h"
#include"iostream"
dae::JumpAnimationComponent::JumpAnimationComponent()
    : m_Elapsed(0.0f)
{
   

}

void  dae::JumpAnimationComponent::SetAcive(bool isactive)
{
    m_IsActive = isactive;
}

void dae::JumpAnimationComponent::Update()
{
    m_pGameObject = GetOwner();

    if (!m_IsActive) return;

    if (m_execute) 
    {
        m_execute = false;
        m_StartPosition = glm::vec3{ m_pGameObject->GetWorldPosition().x , m_pGameObject->GetWorldPosition().y, 0 };


        switch (m_DirectionInt)
        {

        case 0:                        
            m_JumpOffset.x = xStrenght;   
            m_JumpOffset.y = -YStrenght;

           break;

        case 1 :

            m_JumpOffset.x = -xStrenght;  
            m_JumpOffset.y = -YStrenght;

            break;

        case 2:

            m_JumpOffset.x = xStrenght;   
            m_JumpOffset.y = YStrenght;

            break;
        case 3:

            m_JumpOffset.x = -xStrenght;
            m_JumpOffset.y = YStrenght; 

            break;
        


        default:
            break;
        }


            m_EndPosition = m_StartPosition + glm::vec3{ m_JumpOffset.x,m_JumpOffset.y, 0 };
    }

    float deltaTime = SceneManager::GetInstance().GetDeltaTime();
    m_Elapsed += deltaTime;

    if (m_Elapsed >= m_Duration)
    { 
        m_IsActive = false;
        m_execute = true;
        m_Elapsed = 0;
        m_StartPosition = m_EndPosition;
    }

    float t = m_Elapsed / m_Duration;
    glm::vec3 newPosition = glm::mix(m_StartPosition, m_EndPosition, t);
    newPosition.y += std::sin(t * glm::pi<float>()) * m_ArcHeight; // This is the arc height
    m_pGameObject->SetPosition(newPosition.x, newPosition.y);
}

void dae::JumpAnimationComponent::Render()
{
   // Renderer::GetInstance().FillSquare(m_pGameObject->GetWorldPosition().x*2, m_pGameObject->GetWorldPosition().y*2, 30, SDL_Color{255,20,20,200});
   // Renderer::GetInstance().FillSquare(m_pGameObject->GetLocalPosition().x*2, m_pGameObject->GetLocalPosition().y*2, 30, SDL_Color{255,20,20,200});
}

void dae::JumpAnimationComponent::SetDirection(glm::vec3& direction)
{

    m_Direction = direction;
}

void dae::JumpAnimationComponent::SetDirectionInt(int direction)
{
    m_DirectionInt = direction;
}

void dae::JumpAnimationComponent::Reset()
{
    m_IsActive = false;
    m_Elapsed = 0;
    m_execute = true;
}

