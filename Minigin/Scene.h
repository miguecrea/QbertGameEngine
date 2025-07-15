#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class RenderComponent;
	class Scene final
	{
		friend Scene & SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::shared_ptr<GameObject> object);

		void ForceRemove(std::shared_ptr<GameObject> pObject);
		void ForceRemoveAll();
		void DestroyAll();

		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();
		void CheckParentException(std::shared_ptr<GameObject> object) const;

		void Update();
		void Render() const;
		void BeginPlay();
		void CleanUp();

		void FixedUpdate();
		std::string GetName() const;

		void Load();
		bool NeedsCleanUp() const;


		void AddPlayer(std::shared_ptr<GameObject> player);
		void AddPlayer2(std::shared_ptr<GameObject> player);
		void AddMap(std::shared_ptr<GameObject> map);
		void AddEnemy(std::shared_ptr<GameObject> player);
		void AddObjects(std::vector<std::shared_ptr<GameObject>> Obejcts);


		std::shared_ptr<GameObject> m_player = nullptr;
		std::shared_ptr<GameObject> m_player2 = nullptr;
		std::shared_ptr<GameObject> m_Map = nullptr;
		std::vector<std::shared_ptr<GameObject>> m_Obejects;


		std::shared_ptr<dae::RenderComponent> GetPlayerRenderComponent();
		std::shared_ptr<GameObject> m_enemy = nullptr;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void  SetId(int number);
		int GetId() const;
	

	private: 
		explicit Scene(const std::string& name);
		std::string m_name;
		std::vector <std::shared_ptr<GameObject>> m_pObjects{};
		int m_id = 0;

		static unsigned int m_idCounter; 
	
	};

}
