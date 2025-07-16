#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <chrono>
#include <thread>
#include"EventManager.h"
#include <conio.h>
#include"Scene.h"
#include"staticHeader.h"

SDL_Window * g_window{};

class SceneManager;

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
		printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
			version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Minigin::Minigin(const std::string& dataPath)
{
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	//279 x 319

	//16 x 16 
	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		720,          //48 x 15 
		816,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}


void dae::Minigin::Run(const std::function<void()>& load)
{
	srand(static_cast<unsigned int>(time(nullptr)));


		load();

		auto& events = EventManager::GetInstance();
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		//Update loop
		constexpr float desiredFPS{ 144.f };
		constexpr int maxWaitingTimeMs{ static_cast<int>(1000 / desiredFPS) };

		auto lastTime{ std::chrono::high_resolution_clock::now() };
		bool doContinue = true;

		while (doContinue)
		{
			//Update time
			const auto currentTime{ std::chrono::high_resolution_clock::now() };
			const float deltaTime{ std::chrono::duration<float>(currentTime - lastTime).count() };


			lastTime = currentTime;

			//Check input
			doContinue = input.ProcessInput();

			//Update scenes
			sceneManager.Update(deltaTime);

			//Render
			renderer.Render();

			//Update Event Queues
			events.HandleEvents();

			//Delete objects
			sceneManager.CleanUp();

			//Count sleep time
			const auto sleepTime{ currentTime + std::chrono::milliseconds(maxWaitingTimeMs) - std::chrono::high_resolution_clock::now() };

			std::this_thread::sleep_for(sleepTime);

#if DEBUG
			system("cls");
#endif



		}

	sceneManager.ForceRemoveAllObjects();

	

}