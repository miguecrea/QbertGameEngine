#pragma once

#include "Component.h"
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include<vector>
#include"AnimationComponent.h"
#include"DelegateBase.h"

namespace dae
{

	class PengoComponent final : public Component
	{
	public:

		PengoComponent();

		PengoComponent(const PengoComponent& other) = default;
		PengoComponent(PengoComponent&& other) = default;
		PengoComponent& operator=(const PengoComponent& other) = default;
		PengoComponent& operator=(PengoComponent&& other) = default;

		MulticastDelegate <> m_OnPengoBreakOrMove;
	private:

	};
}