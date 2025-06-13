#pragma once
namespace dae
{
	class GameObject;

	class Component
	{
	public:
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		virtual void BeginPlay();

		virtual ~Component() = default;
		Component(const Component& other) = default;
		Component(Component&& other) = default;
		Component& operator=(const Component& other) = default;
		Component& operator=(Component&& other) = default;

		//Owner
		GameObject * GetOwner() const;
		void SetOwner(GameObject* pGameObject);  //understood

		//Priority
		bool operator<(const Component& other) const;

		void SetPriority(int priority);
		int GetPriority() const;
	
	protected:
		explicit Component(int priority = 0);


	private:
		GameObject * m_pOwner{ nullptr };   //it is private we dont want people accesing it just we csan use a setter 
		int m_Priority{ 0 };
	};
}

