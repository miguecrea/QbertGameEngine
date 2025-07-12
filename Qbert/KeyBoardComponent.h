#pragma once

#include"Component.h"
#include"SDL.h"
#include<string>
#include"memory"
namespace dae
{

	class TextComponent;

	//can take ther other component as a parameter the one that remders text
	class KeyBoardComponent : public Component
	{

	public:

		KeyBoardComponent(const char & key,std::shared_ptr< TextComponent> textComponent,float TileSize);
		virtual ~KeyBoardComponent();
		KeyBoardComponent(const KeyBoardComponent& other) = default;
		KeyBoardComponent(KeyBoardComponent&& other) = default;
		KeyBoardComponent& operator=(const KeyBoardComponent& other) = default;
		KeyBoardComponent& operator=(KeyBoardComponent&& other) = default;
		
		void Render() override;
		void Update() override;
		bool m_IsActive = false;
		int m_index = 0;
		int m_ActiveIndex = 0;
		char m_key{};
		float m_TileSize{};

	private:
		std::shared_ptr<TextComponent> m_pTextComponent;

	};


}