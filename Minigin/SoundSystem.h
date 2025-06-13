#pragma once
#include <string>

namespace dae
{
	class SoundSystem
	{
	public:
		SoundSystem() = default;
		virtual ~SoundSystem();

		SoundSystem(const SoundSystem& other) = delete;
		SoundSystem(SoundSystem&& other) = delete;
		SoundSystem& operator=(const SoundSystem& other) = delete;
		SoundSystem& operator=(SoundSystem&& other) = delete;

		virtual void Play(const int soundId, const float volume = 1.f, const int nrLoops = 0) = 0;
		virtual void Preload(const int soundId) = 0;
		virtual void AddSound(const std::string& fileName, int& soundId, bool isMusic) = 0;
		virtual void ToggleMute() = 0;
	};
}
