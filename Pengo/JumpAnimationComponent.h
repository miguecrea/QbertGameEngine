#pragma once

#include "Component.h"
#include <string>
#include <memory>
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;

	class JumpAnimationComponent final : public Component
	{
	public:


        JumpAnimationComponent();
      


		virtual ~JumpAnimationComponent() = default;
		JumpAnimationComponent(const JumpAnimationComponent& other) = default;
		JumpAnimationComponent(JumpAnimationComponent&& other) = default;
		JumpAnimationComponent& operator=(const JumpAnimationComponent& other) = default;
		JumpAnimationComponent& operator=(JumpAnimationComponent&& other) = default;

      

        bool IsActive() const { return m_IsActive; }
        void SetAcive(bool isactive);

        void  Update() override;
        void  Render() override;

        void SetDirection(glm::vec3 & direction);
        void SetDirectionInt(int direction);

        void Reset();



    private:
        GameObject * m_pGameObject;
   
        bool m_IsActive = false;
        float m_TimeUntilActive = 2.f;

        float m_Elapsed = 0.0f;
        const float m_Duration = 1.f; // Duration of the jump
       // const float m_Duration = 1.4f; // Duration of the jump
        const float m_ArcHeight = -10.0f; // Height of the jump
        glm::vec3 m_StartPosition{};
        glm::vec3 m_EndPosition{};
      //  glm::vec3 m_JumpOffset{ -12,20,0 };
        glm::vec3 m_JumpOffset{ 0,0,0 };
        
        glm::vec3 m_Direction{ 0,0,0 };


        int m_DirectionInt = 0;

       // float xStrenght{12};
        //float YStrenght{20}; 
        float xStrenght{12};
        float YStrenght{18};



        bool m_execute = true;


	};
}

