
#pragma once
#include"Component.h"
#include<memory>

namespace dae
{
	class GameObject;

	class TimerAndInputComponent final : public Component
	{
	public:


		TimerAndInputComponent();
		virtual ~TimerAndInputComponent() = default;
		TimerAndInputComponent(const TimerAndInputComponent& other) = default;
		TimerAndInputComponent(TimerAndInputComponent&& other) = default;
		TimerAndInputComponent& operator=(const TimerAndInputComponent& other) = default;
		TimerAndInputComponent& operator=(TimerAndInputComponent&& other) = default;

		void  Update() override;
		void HandleInputBlocking();
		void ResetTimer();
		void  Render() override;
		void StartCount();
		void StartTimer();
		void EndTimer();
		bool GetCanUseInput() const;
		void setCanUseInput(bool value);
		bool IsTimerDone();

	
	private:

		float  m_TimerUntilUsingInput{};
		float  m_TimeUntilUsingInput{1.f};
		const float  MAX_WAITING_TIME{ 2.f };
		bool m_startTimer = false;
		bool m_CanUseInput = true;

	};
}