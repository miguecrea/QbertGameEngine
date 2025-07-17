#pragma once

#include "Component.h"
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include<vector>
#include"AnimationComponent.h"
#include"DelegateBase.h"
#include"PengoDirection.h"

namespace dae
{
		

	class PengoComponent final : public Component
	{
	public:


		Direction m_CurrentDirection{};

		PengoComponent();
		virtual void BeginPlay() override;
		virtual void Render() override;

		PengoComponent(const PengoComponent& other) = default;
		PengoComponent(PengoComponent&& other) = default;
		PengoComponent& operator=(const PengoComponent& other) = default;
		PengoComponent& operator=(PengoComponent&& other) = default;

		MulticastDelegate <Direction,int,int,bool> m_OnPengoBreakOrMove;
	private:

	};
}