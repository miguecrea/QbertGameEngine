#include "EnemyJumpComponent.h"
#include"GameObject.h"
#include"SceneManager.h"
#include"glm/gtc/constants.hpp."
#include"iostream"
#include"Renderer.h"
#include"Audio.h"
#include"staticHeader.h"




dae::EnemyJumpComponent::EnemyJumpComponent(float jumpWaitingTime, float TimeUntilDrawing, TypeOfAi AiType, float JumpDuration):
    m_TypeOfAi{AiType},m_TimeToUpdate{jumpWaitingTime}, m_TimeToStartUpdatingObject{ TimeUntilDrawing }, m_Duration{ JumpDuration }
{
    if (m_TypeOfAi == TypeOfAi::RightLeft || m_TypeOfAi == TypeOfAi::AllRight)
    {
        m_JumpOffset.x = -m_JumpOffset.x;
    }
    
    if (m_TypeOfAi == TypeOfAi::Snake) 
    {
        m_JumpOffset.x = 12;
        m_JumpOffset.y = -20;
    } 
    
    if (m_TypeOfAi == TypeOfAi::SnakeLeft)  //right
    {
      
        //jump right
        m_JumpOffset.x = -12;
        m_JumpOffset.y = -20;

    }


    m_posX[0] = 135; 
    m_posY[0] = 165; 
    
    m_posX[1] = 100;
    m_posY[1] = 148;


    m_posX[2] = 126;
    m_posY[2] = 145;  
    
    m_posX[3] = 87;   
    m_posY[3] = 133;  
    
    m_posX[4] = 75;
    m_posY[4] = 145;


}

void dae::EnemyJumpComponent::Update()
{

    if (!m_Update) return;
 
    m_pGameObject = GetOwner();
    m_TimeUntilActive += SceneManager::GetInstance().GetDeltaTime();
    if (m_TimeUntilActive >= m_TimeToUpdate)   //2.f
    {
        m_TimeUntilActive = 0;
        m_IsActive = true;
        m_execute = true; 
       

    }

    

    if(!m_IsActive) return;

   if(m_execute)
   {                       
       m_execute = false;
      m_StartPosition = glm::vec3{ m_pGameObject->GetWorldPosition().x , m_pGameObject->GetWorldPosition().y, 0};
 


    m_EndPosition = m_StartPosition + glm::vec3{ m_JumpOffset.x,m_JumpOffset.y, 0 };

    




   }



     float deltaTime = SceneManager::GetInstance().GetDeltaTime();
     m_Elapsed += deltaTime;

     if (m_Elapsed >= m_Duration)
     {                                      //1,4f 
         m_Elapsed = m_Duration;
         m_IsActive = false;

         m_Elapsed = 0;

         m_StartPosition = m_EndPosition;


         if (m_TypeOfAi == TypeOfAi::RightLeft || m_TypeOfAi == TypeOfAi::LeftRight)
         {
         m_JumpOffset.x = -m_JumpOffset.x;

         }


         if (m_TypeOfAi == TypeOfAi::Snake)
         {
            m_JumpOffset.x = 12;
             m_JumpOffset.y = -m_JumpOffset.y;

         }   
         if (m_TypeOfAi == TypeOfAi::SnakeLeft)
         {
              m_JumpOffset.x = -12;
              m_JumpOffset.y = -m_JumpOffset.y;

         }




     }

     float t = m_Elapsed / m_Duration;
     glm::vec3 newPosition = glm::mix(m_StartPosition, m_EndPosition, t);
     newPosition.y += std::sin(t * glm::pi<float>()) * m_ArcHeight; // This is the arc height

     m_pGameObject->SetPosition(newPosition.x, newPosition.y);

   //  std::cout << m_pGameObject->GetWorldPosition().x * 2 << " " << m_pGameObject->GetWorldPosition().y * 2 << "\n";



}

void dae::EnemyJumpComponent::Render()
{
    //Renderer::GetInstance().FillSquare(m_StartPosition.x*2, m_StartPosition.y*2,20*2,20, SDL_Color{ 255,0,0,255 });


      //  Renderer::GetInstance().FillSquare(m_EndPosition.x*2, m_EndPosition.y*2,20, SDL_Color{ 255,0,0,255 });
}

void dae::EnemyJumpComponent::SetActive(bool isActive)
{

    m_Update = isActive;
}

void dae::EnemyJumpComponent::Reset()
{

    m_Elapsed = 0;
  
}

void dae::EnemyJumpComponent::ChangeSnakeDirection()
{

    m_JumpOffset.x = -m_JumpOffset.x;
}
