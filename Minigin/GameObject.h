#pragma once
#include <memory>
#include "Transform.h"
#include "Component.h"
#include <vector>
#include<string>

namespace dae
{
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		void Update();
		void FixedUpdate();
		void Render() const;
		void BeginPlay();




		GameObject(int priority = 0);
		virtual ~GameObject();
		GameObject(const GameObject& other) = default;
		GameObject(GameObject&& other) = default;
		GameObject& operator=(const GameObject& other) = default;
		GameObject& operator=(GameObject&& other) = default;



		//Adding child/parent
		void SetParent(GameObject* pGameObject, bool keepWorldPosition = true);
		void AddChild(std::shared_ptr<GameObject> pGameObject, bool keepWorldPosition = true);
		void RemoveChild(std::shared_ptr<GameObject> pGameObject);

		GameObject* GetParent() const;   //getting parent 
		bool CanBeParentOf(GameObject* pChild) const;  //boleasm

		void AddComponent(std::shared_ptr<Component> pComponent);

		template<typename ComponentType>
		std::shared_ptr<ComponentType> GetComponent()
		{
			for (const auto& pComponent : m_pComponents)
			{
				if (auto pTargetComponent = std::dynamic_pointer_cast<ComponentType>(pComponent)) 
				{
					return pTargetComponent;
				}
			}
			return nullptr;
		}

		template<typename ComponentType>
		bool HasComponentType()
		{
			for (const auto& pComponent : m_pComponents)
			{
				if (auto pTargetComponent = std::dynamic_pointer_cast<ComponentType>(pComponent))
				{
					return true;
				}
			}
			return false;
		}

		//Transform
		void SetPosition(float x, float y);
		glm::vec3 GetWorldPosition();
		glm::vec3 GetLocalPosition() const;
		void SavePosition(float x,float y);
		glm::vec3 GetSavedPosition() const;
		

		//Priority
		int GetPriority() const;

		//Destruction
		void Destroy();
		bool IsDestroyed() const;

		void AddTag(std::string tag);

		std::string GetTag() const ;



	
		void UpdatePos(float x,float y);

	private:
		//Child/parent
		std::vector<std::shared_ptr<GameObject>> m_pChildren{};       //vector of game objects that are his children 
		GameObject* m_pParent{};
		void SortChildren();

		std::string m_tag{ "NoTag" };
		//Components
		std::vector<std::shared_ptr<Component>> m_pComponents{};  //vector of it is compoensts 
		
		//Transform
		void SetTransformDirty();

		Transform m_Transform{};    //local position and world 


		bool m_IsTransformDirty{ true };
		//Priority
		const int m_Priority{ 0 };
		glm::vec3 m_savedPos{};

		//Destruction
		bool m_IsDestroyed{ false };

	};

}
