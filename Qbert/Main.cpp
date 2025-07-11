#include <SDL.h>
#include <iostream>
#include"FPSComponent.h"
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "Scene.h"

#include "UpdatePositionCommand.h"
#include "SetPositionCommand.h"
#include <memory>
#include "RenderComponent.h"
#include "GameObject.h"
#include "Controller.h"
#include "Keyboard.h"
#include"RotatorComponent.h"
#include"AnimationComponent.h"
#include"StartInfoComponent.h"
#include<iostream>
#include"Renderer.h"
#include"Renderer.h"
#include"TextComponent.h"
#include"ResourceManager.h"
#include"Renderer.h"

#include"NextSceneCommand.h"
#include"SoundSystem.h"
#include"Audio.h"
#include"LoggingSystem.h"
#include"SDL_SoundSystem.h"
#include"LoggingSoundSystem.h"
#include"staticHeader.h"
#include"SceneManager.h"
#include"LivesComponent.h"
#include"HighScoreComponent.h"
#include"ToggleMuteCommand.h"
#include"JumpAnimationComponent.h"
#include"RectangleComponent.h"
#include"CollisionComponent.h"
#include"SkipLevelsCommand.h"
#include"QbertDirection.h"
#include "Main.h"
#include"CollisionWithComponent.h"
#include"FreeFallComponent.h"
#include"TagComponent.h"
#include"TimerAndInputComponent.h"
#include"KeyBoardComponent.h"
#include"ChangeSelectionCommand.h"
#include"LockInCommand.h"
#include"stringAndScoresVariables.h"
#include"DisplayNameComponent.h"
#include"RotatingCharacterMoveComponent.h"
#include"EnemyJumpComponent.h"
#include"TypeOfAi.h"
#include"CurseQbertComponent.h"
#include"CollsionResponse.h"
#include"TagManager.h"
#include"DebugRenderComponent.h"
#include"ChangeModeCommand.h"
#include"MoveGridCommand.h"
#include"SaveLevelComponent.h"
#include"OpenLevelCommand.h"
#include"MoveGridCommand.h"
#include"TestCommand.h"
#include"PengoComponent.h"

std::shared_ptr<dae::GameObject> CreatePinkDot(dae::Scene& scene, std::vector<std::shared_ptr<dae::GameObject>>& enemiesvector, float TimeToUpdate, float TimeOnAir, TypeOfAi ai);
std::shared_ptr<dae::GameObject> CreateGreenDot(dae::Scene& scene, std::vector<std::shared_ptr<dae::GameObject>>& enemiesvector, float TimeToUpdate, float TimeOnAir, TypeOfAi ai);
std::shared_ptr<dae::GameObject> CreateRedDot(dae::Scene& scene, std::vector<std::shared_ptr<dae::GameObject>>& enemiesvector, float TimeToUpdate, float TimeOnAir, TypeOfAi ai,std::string Filename);
std::shared_ptr<dae::GameObject> CreateSnake(dae::Scene& scene, std::vector<std::shared_ptr<dae::GameObject>>& enemiesvector);
std::shared_ptr<dae::GameObject> CreateQbert(dae::Scene& scene, int leve, float xpos, float ypos, std::vector < std::shared_ptr<dae::GameObject>>& cubesVector, std::vector<std::shared_ptr<dae::GameObject>>& enemies);
std::shared_ptr<dae::GameObject> CreateQbertTutorial(dae::Scene& scene, int leve, float xpos, float ypos, std::vector < std::shared_ptr<dae::GameObject>>& cubesVector, std::vector<std::shared_ptr<dae::GameObject>>& enemies);
std::shared_ptr<dae::GameObject> CreateButton(dae::Scene& scene, const std::string& message, float x, float y, const SDL_Color& color, int size,const std::string & SaveLevelComponent);
void  LevelText(int index, dae::Scene& scene);
void  LevelText2(int index, dae::Scene& scene);
void DrawNumber2(dae::Scene& scene, int index);

std::vector<std::shared_ptr<dae::GameObject>> AddTutorialMap(dae::Scene& scene);
enum class Level
{
	Level1 = 1,
	Level2,
	Level3
};


void  LoadMenuScene()
{
	auto & MenuScene = dae::SceneManager::GetInstance().CreateScene("MenuScene");
	auto& input2 = dae::InputManager::GetInstance();

	auto controller = input2.AddController();
	auto keyboard{ input2.GetKeyboard() };


	std::unique_ptr<dae::Command> SetSceneCommand{ std::make_unique<dae::NextSceneCommand>("SinglePlayerScene",GameMode::SinglePlayer) };// one of when isntantiating a class 
	keyboard->MapCommandToButton(SDL_SCANCODE_1, std::move(SetSceneCommand), dae::ButtonState::Up);


	std::unique_ptr<dae::Command> SkipLevelsCommand{ std::make_unique<dae::SkipLevelsCommand>() };// one of when isntantiating a class 
	keyboard->MapCommandToButton(SDL_SCANCODE_F1, std::move(SkipLevelsCommand), dae::ButtonState::Up);


	SetSceneCommand = std::make_unique<dae::NextSceneCommand>("CoOpScene", GameMode::Coop);
	keyboard->MapCommandToButton(SDL_SCANCODE_2, std::move(SetSceneCommand), dae::ButtonState::Up);

	SetSceneCommand = std::make_unique<dae::NextSceneCommand>("VersusMode", GameMode::Versus);
	keyboard->MapCommandToButton(SDL_SCANCODE_3, std::move(SetSceneCommand), dae::ButtonState::Up);

	SetSceneCommand = std::make_unique<dae::NextSceneCommand>("InputNameScene", GameMode::Versus);
	keyboard->MapCommandToButton(SDL_SCANCODE_4, std::move(SetSceneCommand), dae::ButtonState::Up);

	SetSceneCommand = std::make_unique<dae::ToggleMuteCommand>();  //mute
	keyboard->MapCommandToButton(SDL_SCANCODE_9, std::move(SetSceneCommand), dae::ButtonState::Up);


	auto MapGameObject = std::make_shared<dae::GameObject>();
	auto MapRender = std::make_shared<dae::RenderComponent>(-1, false); 
	MapRender->SetTexture("BackGroundPengo.png");
	MapRender->SetDimension(3.f);
	MapGameObject->AddComponent(MapRender);
	MapGameObject->SetPosition(0,0);
	MenuScene.Add(MapGameObject);

	auto PengoLogoObject = std::make_shared<dae::GameObject>();
	auto PengoLogoRender = std::make_shared<dae::RenderComponent>(-1, false); 
	PengoLogoRender->SetTexture("PengoLogo.png");
	PengoLogoRender->SetDimension(1.f);
	PengoLogoObject->AddComponent(PengoLogoRender);
	PengoLogoObject->SetPosition(40,30);
	MenuScene.Add(PengoLogoObject);






	float xPos{ 80 };
	float yPos{ 450.f };
	float Offset{ 50};
	int letterSize{ 40 };

	SDL_Color green = { 0,255,0,255 };


	std::vector<std::shared_ptr<dae::GameObject>>TextGameObjects{};

	TextGameObjects.push_back(CreateButton(MenuScene, "SinglePlayer - Press 1", xPos, yPos, green, letterSize,"SinglePlayerScene"));
	yPos += Offset;
	TextGameObjects.push_back(CreateButton(MenuScene, "CoperativeMode - Press 2", xPos, yPos, green, letterSize,"CoOpScene"));
	yPos += Offset;
	TextGameObjects.push_back(CreateButton(MenuScene, "VersusMode- Press 3 ", xPos, yPos, green, letterSize,"VersusMode"));
	yPos += Offset;
	TextGameObjects.push_back(CreateButton(MenuScene, "InputName - Press 4 ", xPos, yPos, green, letterSize,"InputNameScene"));
	

//	std::unique_ptr<dae::MoveGridCommand> MoveGrid{ }; 


	std::unique_ptr<dae::ChangeModeCommand> ChangeMode = std::make_unique<dae::ChangeModeCommand>(TextGameObjects);
	std::unique_ptr<dae::OpenLevelCommand> OpenLevelCommand = std::make_unique<dae::OpenLevelCommand>(TextGameObjects, ChangeMode.get());

	controller->MapCommandToThumbstick(dae::Controller::ControllerThumbsticks::LeftThumbstick,std::move(ChangeMode));
	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonA,std::move(OpenLevelCommand),dae::ButtonState::Up);


	


}



void Level1TutoriaL()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("level1tutorial");
	scene.SetId(1);

	auto cubesVector = AddTutorialMap(scene);

	std::vector < std::shared_ptr<dae::GameObject>> m_enemiesVector;

	float InitialPosX{ 96 };
	float InitialPosY{ 59 };

	auto Qbert = CreateQbertTutorial(scene, int(Level::Level1), InitialPosX, InitialPosY, cubesVector, m_enemiesVector);

	//q bert parameters are the level and the pos

	LevelText(0, scene);
	DrawInvisibleDotsTutorial(Qbert, scene);     
	DrawBottomRectTutorial(Qbert, scene);

	DrawNumber(scene, 0);
	DisplayLives(scene);

}
void DisplayLives(dae::Scene& scene)
{
	auto PlayerScore = std::make_shared<dae::GameObject>();
	auto PlayerScoreRenderer = std::make_shared<dae::RenderComponent>();
	auto pTextComponent2 = std::make_shared<dae::TextComponent>(PlayerScoreRenderer, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24));
	auto playerScoreComponent = std::make_shared<dae::DisplayNameComponent>(pTextComponent2);
	playerScoreComponent->m_IsLives = true;  //change 
	pTextComponent2->SetColor({ 0,255,255 });
	PlayerScore->AddComponent(pTextComponent2);
	PlayerScore->AddComponent(playerScoreComponent);
	PlayerScore->AddComponent(PlayerScoreRenderer);
	PlayerScore->SetPosition(100, 10);
	scene.Add(PlayerScore);
}
void DrawNumber(dae::Scene& scene, int level)
{

	auto NumberText = std::make_shared<dae::GameObject>();
	auto NumberTextRenderer = std::make_shared<dae::RenderComponent>(-2, true);
	NumberTextRenderer->SetTexture("numbersOneColumn.png");
	NumberTextRenderer->SetDimension(0.83f);       //was 0.5     
	NumberTextRenderer->AddToVector(3, 1, 1, 0, dae::AnimationComponent::Type::loop, 0, level);

	NumberText->AddComponent(NumberTextRenderer);

	NumberText->SetPosition(75, 188);
	scene.Add(NumberText);

}
void DrawInvisibleDotsTutorial(std::shared_ptr<dae::GameObject>& Qbert, dae::Scene& scene)
{
	float x{ 110 };
	float Y{ 50 };
	float YOffset{ 18 };
	float XOffset{ 12 };
	const int NumberRects = 3;
	//  invisible rect

	for (int index = 0; index < NumberRects; index++)
	{
		auto InvisibleRect = std::make_shared<dae::GameObject>();
		auto RectComponentInvisible = std::make_shared<dae::RectangleComponent>(14, 14);
		auto TagComponentInvisibleRect = std::make_shared<dae::TagComponent>("InvisibleRect");
		auto CollidesWithCharacter = std::make_shared<dae::CollisionWithComponent>(Qbert);
		auto CollisionResponse = std::make_shared<dae::CollsionResponse>();  //if can //set can collide to no

		InvisibleRect->AddComponent(RectComponentInvisible);
		InvisibleRect->AddComponent(TagComponentInvisibleRect);
		InvisibleRect->AddComponent(CollidesWithCharacter);
		InvisibleRect->AddComponent(CollisionResponse);
		InvisibleRect->SetPosition(x + XOffset * index, Y + YOffset * index);
		scene.Add(InvisibleRect);

	}

	x = 90;
	XOffset = -XOffset;
	for (int index = 0; index < 3; index++)
	{
		auto InvisibleRect = std::make_shared<dae::GameObject>();
		auto RectComponentInvisible = std::make_shared<dae::RectangleComponent>(10, 10);
		auto TagComponentInvisibleRect = std::make_shared<dae::TagComponent>("InvisibleRect");
		auto CollidesWithCharacter = std::make_shared<dae::CollisionWithComponent>(Qbert);
		auto CollisionResponse = std::make_shared<dae::CollsionResponse>();  //if can //set can collide to no


		InvisibleRect->AddComponent(RectComponentInvisible);
		InvisibleRect->AddComponent(TagComponentInvisibleRect);
		InvisibleRect->AddComponent(CollidesWithCharacter);
		InvisibleRect->AddComponent(CollisionResponse);
		InvisibleRect->SetPosition(x + XOffset * index, Y + YOffset * index);
		scene.Add(InvisibleRect);

	}
	x += 35;
	Y += 50;
	for (int index = 0; index < 3; index++)
	{
		auto InvisibleRect = std::make_shared<dae::GameObject>();
		auto RectComponentInvisible = std::make_shared<dae::RectangleComponent>(13, 13);
		auto TagComponentInvisibleRect = std::make_shared<dae::TagComponent>("InvisibleRect");
		auto CollidesWithCharacter = std::make_shared<dae::CollisionWithComponent>(Qbert);
		auto CollisionResponse = std::make_shared<dae::CollsionResponse>();  //if can //set can collide to no

		InvisibleRect->AddComponent(RectComponentInvisible);
		InvisibleRect->AddComponent(TagComponentInvisibleRect);
		InvisibleRect->AddComponent(CollidesWithCharacter);
		InvisibleRect->AddComponent(CollisionResponse);
		InvisibleRect->SetPosition(x + XOffset * index, Y + YOffset * index);
		scene.Add(InvisibleRect);

	}
	x -= 60;
	XOffset = -XOffset;
	for (int index = 0; index < 3; index++)
	{
		auto InvisibleRect = std::make_shared<dae::GameObject>();
		auto RectComponentInvisible = std::make_shared<dae::RectangleComponent>(10, 10);
		auto TagComponentInvisibleRect = std::make_shared<dae::TagComponent>("InvisibleRect");
		auto CollidesWithCharacter = std::make_shared<dae::CollisionWithComponent>(Qbert);
		auto CollisionResponse = std::make_shared<dae::CollsionResponse>();  //if can //set can collide to no
		InvisibleRect->AddComponent(RectComponentInvisible);
		InvisibleRect->AddComponent(TagComponentInvisibleRect);
		InvisibleRect->AddComponent(CollidesWithCharacter);
		InvisibleRect->AddComponent(CollisionResponse);

		InvisibleRect->SetPosition(x + XOffset * index, Y + YOffset * index);
		scene.Add(InvisibleRect);

	}

}
void DrawBottomRectTutorial(std::shared_ptr<dae::GameObject>& Qbert, dae::Scene& scene)
{
	int width{ 450 };
	int Height{ 20 };
	auto BottomRect = std::make_shared<dae::GameObject>();
	auto RectComponentBottomRect = std::make_shared<dae::RectangleComponent>(width, Height);
	auto TagComponentBottomRect = std::make_shared<dae::TagComponent>("BottomRect");
	auto CollideWithComponentBottomRect = std::make_shared<dae::CollisionWithComponent>(Qbert);
	auto CollisionResponse = std::make_shared<dae::CollsionResponse>();  //if can //set can collide to no

	CollideWithComponentBottomRect->SetTutorial(true);
	BottomRect->AddComponent(RectComponentBottomRect);    //change the logic so it is different 
	BottomRect->AddComponent(TagComponentBottomRect);
	BottomRect->AddComponent(CollideWithComponentBottomRect);
	BottomRect->AddComponent(CollisionResponse);
	BottomRect->SetPosition(0, 250);
	scene.Add(BottomRect);



}
void Level2TutoriaL()
{

	auto& scene = dae::SceneManager::GetInstance().CreateScene("level2tutorial");
	scene.SetId(3);

	auto cubesVector = AddTutorialMap(scene);
	float InitialPosX{ 96 };
	float InitialPosY{ 59 };

	std::vector<std::shared_ptr<dae::GameObject>> m_enemiesVector;
	LevelText(1, scene);
	auto Qbert = CreateQbertTutorial(scene, int(Level::Level2), InitialPosX, InitialPosY, cubesVector, m_enemiesVector);
	DrawInvisibleDotsTutorial(Qbert, scene);
	DrawBottomRectTutorial(Qbert, scene);
	DrawNumber(scene, 1);
	DisplayLives(scene);

}

void Level3TutoriaL()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("level3tutorial");
	scene.SetId(5);

	auto CubesVector = AddTutorialMap(scene);

	std::vector < std::shared_ptr<dae::GameObject>> m_enemiesVector;

	float InitialPosX{ 96 };
	float InitialPosY{ 59 };

	auto Qbert = CreateQbertTutorial(scene, int(Level::Level3), InitialPosX, InitialPosY, CubesVector, m_enemiesVector);
	LevelText(2, scene);
	DrawInvisibleDotsTutorial(Qbert, scene);
	DrawBottomRectTutorial(Qbert, scene);
	DrawNumber(scene, 2);
	DisplayLives(scene);
}


void Level1()
{

	auto & scene = dae::SceneManager::GetInstance().CreateScene("SinglePlayerScene");
	scene.SetId(2);

	/// map behind
	
	auto BackGroundGameObject = std::make_shared<dae::GameObject>();
	auto BackGroundImageRender = std::make_shared<dae::RenderComponent>(-1, false);
	BackGroundImageRender->SetTexture("Border.png");
	BackGroundImageRender->SetDimension(2.6f);
	BackGroundGameObject->AddComponent(BackGroundImageRender);
	BackGroundGameObject->SetPosition(-5,0);
	scene.Add(BackGroundGameObject);


	auto PengoGameObject = std::make_shared<dae::GameObject>();
	auto PengoRenderer = std::make_shared<dae::RenderComponent>(-2, true);
	auto PengoComponent = std::make_shared<dae::PengoComponent>();

	PengoRenderer->SetTexture("Pengo.png");
	PengoRenderer->SetDimension(2.4f);       //was 0.5     
	PengoRenderer->AddToVector(3,8,2,5, dae::AnimationComponent::Type::loop,0, 0);//down
	PengoRenderer->AddToVector(3,8,4,5, dae::AnimationComponent::Type::StartAtNoZero,2, 0);//left
	PengoRenderer->AddToVector(3,8,6,5, dae::AnimationComponent::Type::StartAtNoZero,4, 0); //up
	PengoRenderer->AddToVector(3,8,8,5, dae::AnimationComponent::Type::StartAtNoZero,6, 0); //right
	PengoGameObject->AddComponent(PengoComponent);
	PengoGameObject->AddComponent(PengoRenderer);
	PengoGameObject->SetPosition(100.f, 100);
	scene.Add(PengoGameObject);
	scene.AddPlayer(PengoGameObject);

	//diamond
	auto MapGameObject = std::make_shared<dae::GameObject>();
	auto MapComponent = std::make_shared<dae::MapComponent>(PengoGameObject);  // File to read from 
	MapGameObject->AddComponent(MapComponent);
	scene.Add(MapGameObject);
	scene.AddMap(MapGameObject);




}

void CreateBottomRectEnemies(std::shared_ptr<dae::GameObject> & PinkDot, dae::Scene& scene)
{
	int width{ 450 };
	int Height{ 40 };
	auto BottomRect = std::make_shared<dae::GameObject>();
	auto RectComponentBottomRect = std::make_shared<dae::RectangleComponent>(width, Height);
	auto TagComponentBottomRect = std::make_shared<dae::TagComponent>("BottomRect");
	auto CollideWithComponentBottomRect = std::make_shared<dae::CollisionWithComponent>(PinkDot);
	auto CollisionResponse = std::make_shared<dae::CollsionResponse>();  

	CollideWithComponentBottomRect->SetIsAi(true);
	BottomRect->AddComponent(RectComponentBottomRect);
	BottomRect->AddComponent(TagComponentBottomRect);
	BottomRect->AddComponent(CollideWithComponentBottomRect);
	BottomRect->AddComponent(CollisionResponse);
	BottomRect->SetPosition(0, 230);
	scene.Add(BottomRect);
}

void DrawButtonRectSnake(std::shared_ptr<dae::GameObject>& Snake, dae::Scene& scene)
{
	auto BottomRectSnake = std::make_shared<dae::GameObject>();
	auto RectComponentBottomRectSnake = std::make_shared<dae::RectangleComponent>(450, 40);
	auto TagComponentBottomRectSnake = std::make_shared<dae::TagComponent>("BottomRect");
	auto CollideWithComponentBottomRectSnake = std::make_shared<dae::CollisionWithComponent>(Snake);
	auto CollisionResponse = std::make_shared<dae::CollsionResponse>();

	BottomRectSnake->AddComponent(RectComponentBottomRectSnake);    //change the logic so it is different 
	BottomRectSnake->AddComponent(TagComponentBottomRectSnake);
	BottomRectSnake->AddComponent(CollideWithComponentBottomRectSnake);
	BottomRectSnake->AddComponent(CollisionResponse);
	BottomRectSnake->SetPosition(0, 215);
	scene.Add(BottomRectSnake);
}

void CreatePlatforms(std::shared_ptr<dae::GameObject>& Qbert, dae::Scene& scene)
{
	auto Platform = std::make_shared<dae::GameObject>();
	auto PlatformRenderer = std::make_shared<dae::RenderComponent>(-2, true);
	PlatformRenderer->SetTexture("platform.png");
	PlatformRenderer->SetDimension(0.5f);         //HAVE TWO players so they get hidden when they use theb platform
	PlatformRenderer->AddToVector(1, 5, 5, 7, dae::AnimationComponent::Type::loop, 0, 0);
	auto RectComponentPlatfrom = std::make_shared<dae::RectangleComponent>(20, 20);
	auto TagComponentPlatfrom = std::make_shared<dae::TagComponent>("Platform");
	auto CollideWithComponentPlatform = std::make_shared<dae::CollisionWithComponent>(Qbert);
	auto CollisionResponse = std::make_shared<dae::CollsionResponse>();

	Platform->AddComponent(PlatformRenderer);
	Platform->AddComponent(RectComponentPlatfrom);
	Platform->AddComponent(TagComponentPlatfrom);
	Platform->AddComponent(CollideWithComponentPlatform);
	Platform->AddComponent(CollisionResponse);
	Platform->SetPosition(47, 130);
	scene.Add(Platform);



	//LEFT
	/////////////////////////////////

	auto rotatingCharacter = std::make_shared<dae::GameObject>();
	auto rotatingCharacterRenderer = std::make_shared<dae::RenderComponent>(-2, true);
	rotatingCharacterRenderer->SetVisibility(false);   //SO IT DOES NOT SHOW AT FIRST
	auto rotatingCharacterRectComponent = std::make_shared<dae::RectangleComponent>(40, 40);
	rotatingCharacterRectComponent->AddOffset(5, 5);




	auto rotatingCharacterMoveToComponent = std::make_shared<dae::RotatingCharacterMoveComponent>();
	rotatingCharacterMoveToComponent->SetWaitingTime(1);///////
	auto TagComponentRotatingCharacter = std::make_shared<dae::TagComponent>("RotatingCharacter");
	auto collisionComponentRotatingCharacter = std::make_shared<dae::CollisionWithComponent>(Qbert);
	auto CollisionResponse2 = std::make_shared<dae::CollsionResponse>();


	rotatingCharacterRenderer->SetTexture("rotatingCharacter.png");
	rotatingCharacterRenderer->SetDimension(0.3f);         //HAVE TWO players so they get hidden when they use theb platform
	rotatingCharacterRenderer->AddToVector(1, 6, 6, 7, dae::AnimationComponent::Type::loop, 0, 0);  //right
	rotatingCharacter->AddComponent(rotatingCharacterRenderer);
	rotatingCharacter->AddComponent(rotatingCharacterRectComponent);
	rotatingCharacter->AddComponent(rotatingCharacterMoveToComponent);
	rotatingCharacter->AddComponent(TagComponentRotatingCharacter);
	rotatingCharacter->AddComponent(collisionComponentRotatingCharacter);
	rotatingCharacter->AddComponent(CollisionResponse2);
	rotatingCharacter->SetPosition(35, 120);
	scene.Add(rotatingCharacter);


	auto Platform2 = std::make_shared<dae::GameObject>();
	auto PlatformRenderer2 = std::make_shared<dae::RenderComponent>(-2, true);
	PlatformRenderer2->SetTexture("platform.png");
	PlatformRenderer2->SetDimension(0.5f);         //HAVE TWO players so they get hidden when they use theb platform
	PlatformRenderer2->AddToVector(1, 5, 5, 7, dae::AnimationComponent::Type::loop, 0, 0);
	auto RectComponentPlatfrom2 = std::make_shared<dae::RectangleComponent>(20, 20);
	auto TagComponentPlatfrom2 = std::make_shared<dae::TagComponent>("Platform");
	auto CollideWithComponentPlatform2 = std::make_shared<dae::CollisionWithComponent>(Qbert);
	auto CollisionResponse3 = std::make_shared<dae::CollsionResponse>();


	Platform2->AddComponent(PlatformRenderer2);
	Platform2->AddComponent(RectComponentPlatfrom2);
	Platform2->AddComponent(TagComponentPlatfrom2);
	Platform2->AddComponent(CollideWithComponentPlatform2);
	Platform2->AddComponent(CollisionResponse3);
	Platform2->SetPosition(180, 180);
	scene.Add(Platform2);

	auto rotatingCharacter2 = std::make_shared<dae::GameObject>();
	auto rotatingCharacterRenderer2 = std::make_shared<dae::RenderComponent>(-2, true);
	rotatingCharacterRenderer2->SetVisibility(false);   //SO IT DOES NOT SHOW AT FIRST
	auto rotatingCharacterRectComponent2 = std::make_shared<dae::RectangleComponent>(40, 40);
	rotatingCharacterRectComponent2->AddOffset(5, 5);

	auto rotatingCharacterMoveToComponent2 = std::make_shared<dae::RotatingCharacterMoveComponent>();
	rotatingCharacterMoveToComponent2->SetWaitingTime(3);
	rotatingCharacterMoveToComponent2->SetSpeed(30.f);
	auto TagComponentRotatingCharacter2 = std::make_shared<dae::TagComponent>("RotatingCharacter");
	auto collisionComponentRotatingCharacter2 = std::make_shared<dae::CollisionWithComponent>(Qbert);
	auto CollisionResponse4= std::make_shared<dae::CollsionResponse>();


	rotatingCharacterRenderer2->SetTexture("rotatingCharacter.png");
	rotatingCharacterRenderer2->SetDimension(0.3f);         //HAVE TWO players so they get hidden when they use theb platform
	rotatingCharacterRenderer2->AddToVector(1, 6, 6, 7, dae::AnimationComponent::Type::loop, 0, 0);  //right
	rotatingCharacter2->AddComponent(rotatingCharacterRenderer2);
	rotatingCharacter2->AddComponent(rotatingCharacterRectComponent2);
	rotatingCharacter2->AddComponent(rotatingCharacterMoveToComponent2);
	rotatingCharacter2->AddComponent(TagComponentRotatingCharacter2);
	rotatingCharacter2->AddComponent(collisionComponentRotatingCharacter2);
	rotatingCharacter2->AddComponent(CollisionResponse4);
	rotatingCharacter2->SetPosition(177, 170);
	scene.Add(rotatingCharacter2);

}

void DisplayScore(dae::Scene& scene)
{
	auto PlayerScore = std::make_shared<dae::GameObject>();
	auto PlayerScoreRenderer = std::make_shared<dae::RenderComponent>();
	auto pTextComponent2 = std::make_shared<dae::TextComponent>(PlayerScoreRenderer, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24));
	auto playerScoreComponent = std::make_shared<dae::DisplayNameComponent>(pTextComponent2);
	playerScoreComponent->m_IsScore = true;  //change 
	pTextComponent2->SetColor({ 0,255,0 });
	PlayerScore->AddComponent(pTextComponent2);
	PlayerScore->AddComponent(playerScoreComponent);
	PlayerScore->AddComponent(PlayerScoreRenderer);
	PlayerScore->SetPosition(10, 25);
	scene.Add(PlayerScore);
}

void DrawDetails(dae::Scene& scene)
{
	auto Details = std::make_shared<dae::GameObject>();
	auto DetailsRenderer = std::make_shared<dae::RenderComponent>(-2, true);
	DetailsRenderer->SetTexture("details.png");
	DetailsRenderer->SetDimension(3.5f);
	DetailsRenderer->AddToVector(3, 1, 0, 0, dae::AnimationComponent::Type::loop, 0, 0);  //right
	Details->AddComponent(DetailsRenderer);
	Details->SetPosition(150, 60);
	scene.Add(Details);


	//change to 
	auto Details2 = std::make_shared<dae::GameObject>();
	auto DetailsRenderer2 = std::make_shared<dae::RenderComponent>(-2, true);
	DetailsRenderer2->SetTexture("details.png");
	DetailsRenderer2->SetDimension(3.5f);
	DetailsRenderer2->AddToVector(3, 1, 0, 0, dae::AnimationComponent::Type::loop, 0, 2);  //right
	Details2->AddComponent(DetailsRenderer2);
	Details2->SetPosition(10, 40);
	scene.Add(Details2);

}

void PlayerText(dae::Scene& scene)
{
	auto PlayerText = std::make_shared<dae::GameObject>();
	auto PlayerTextRenderer = std::make_shared<dae::RenderComponent>(-2, true);
	PlayerTextRenderer->SetTexture("PlayerText.png");
	PlayerTextRenderer->SetDimension(3.f);         //HAVE TWO players so they get hidden when they use theb platform
	PlayerTextRenderer->AddToVector(2, 1, 0, 0, dae::AnimationComponent::Type::loop, 0, 0);  //right
	PlayerText->AddComponent(PlayerTextRenderer);
	PlayerText->SetPosition(10, 10);
	scene.Add(PlayerText);
}

void ChangeToCube(dae::Scene& scene, int index)
{
	auto CurrentCube = std::make_shared<dae::GameObject>();
	auto CurrentCubeRenderer = std::make_shared<dae::RenderComponent>(-2, true);
	CurrentCubeRenderer->SetTexture("actualCube.png");
	CurrentCubeRenderer->SetDimension(0.4f);
	CurrentCubeRenderer->AddToVector(6, 1, 0, 0, dae::AnimationComponent::Type::loop, 0, index); //NEED TO ADD MORE TO ITTTT   //THE OTHER CUBES 


	CurrentCube->AddComponent(CurrentCubeRenderer);
	CurrentCube->SetPosition(40, 55);
	scene.Add(CurrentCube);
}

void DrawButtonRectMainLevel(std::shared_ptr<dae::GameObject>& Qbert, dae::Scene& scene)
{
	int width{ 450 };
	int Height{ 40 };
	auto BottomRect = std::make_shared<dae::GameObject>();
	auto RectComponentBottomRect = std::make_shared<dae::RectangleComponent>(width, Height);
	auto TagComponentBottomRect = std::make_shared<dae::TagComponent>("BottomRect");
	auto CollideWithComponentBottomRect = std::make_shared<dae::CollisionWithComponent>(Qbert);
	auto CollisionResponse = std::make_shared<dae::CollsionResponse>();

	BottomRect->AddComponent(RectComponentBottomRect);    //change the logic so it is different 
	BottomRect->AddComponent(TagComponentBottomRect);
	BottomRect->AddComponent(CollideWithComponentBottomRect);
	BottomRect->AddComponent(CollisionResponse);
	BottomRect->SetPosition(0, 230);
	scene.Add(BottomRect);


}

void DrawInvisibleDotsmainLevel(std::shared_ptr<dae::GameObject>& Qbert, dae::Scene& scene)
{
	float x{ 110 };
	float Y{ 75 };
	float YOffset{ 18 };
	float XOffset{ 12 };

	for (int index = 0; index < 7; index++)
	{
		auto InvisibleRect = std::make_shared<dae::GameObject>();
		auto RectComponentInvisible = std::make_shared<dae::RectangleComponent>(15, 15);
		auto TagComponentInvisibleRect = std::make_shared<dae::TagComponent>("InvisibleRect");
		auto CollidesWithCharacter = std::make_shared<dae::CollisionWithComponent>(Qbert);  
		auto CollisionResponse = std::make_shared<dae::CollsionResponse>(); 

		InvisibleRect->AddComponent(RectComponentInvisible);
		InvisibleRect->AddComponent(TagComponentInvisibleRect);
		InvisibleRect->AddComponent(CollidesWithCharacter);
		InvisibleRect->AddComponent(CollisionResponse);
		InvisibleRect->SetPosition(x + XOffset * index, Y + YOffset * index);

		if (index == 6) continue;
		scene.Add(InvisibleRect);

	}

	float x2{ 90 };
	float Y2{ 80 };
	float YOffset2{ 18 };
	float XOffset2{ -12 };
	
	for (int index = 0; index < 7; index++)
	{
		auto InvisibleRect = std::make_shared<dae::GameObject>();
		auto RectComponentInvisible = std::make_shared<dae::RectangleComponent>(10, 10);
		auto TagComponentInvisibleRect = std::make_shared<dae::TagComponent>("InvisibleRect");
		auto CollidesWithCharacter = std::make_shared<dae::CollisionWithComponent>(Qbert);  
		auto CollisionResponse = std::make_shared<dae::CollsionResponse>();  

		InvisibleRect->AddComponent(RectComponentInvisible);
		InvisibleRect->AddComponent(TagComponentInvisibleRect);
		InvisibleRect->AddComponent(CollidesWithCharacter);
		InvisibleRect->AddComponent(CollisionResponse);
		InvisibleRect->SetPosition(x2 + XOffset2 * index, Y2 + YOffset2 * index);

		if (index == 3) continue;

		scene.Add(InvisibleRect);

	}

	float x3{ 10 };
	float Y3{ 220 };
	float XOffset3{ 15 };

	for (int index = 0; index < 15; index++)
	{
		auto InvisibleRect = std::make_shared<dae::GameObject>();
		auto RectComponentInvisible = std::make_shared<dae::RectangleComponent>(13, 13);   
		auto TagComponentInvisibleRect = std::make_shared<dae::TagComponent>("InvisibleRect");
		auto CollidesWithCharacter = std::make_shared<dae::CollisionWithComponent>(Qbert);  
		auto CollisionResponse = std::make_shared<dae::CollsionResponse>();

		InvisibleRect->AddComponent(RectComponentInvisible);
		InvisibleRect->AddComponent(TagComponentInvisibleRect);
		InvisibleRect->AddComponent(CollidesWithCharacter);
		InvisibleRect->AddComponent(CollisionResponse);
		InvisibleRect->SetPosition(x3 + XOffset3 * index, Y3);
		scene.Add(InvisibleRect);

	}
}

void DrawInvisibleDotsmainSnake(std::shared_ptr<dae::GameObject>& Qbert, dae::Scene& scene)
{

	float x{ 110 };
	float Y{ 75 };
	float YOffset{ 18 };
	float XOffset{ 12 };

	for (int index = 0; index < 7; index++)
	{
		auto InvisibleRect = std::make_shared<dae::GameObject>();
		auto RectComponentInvisible = std::make_shared<dae::RectangleComponent>(15, 15);    
		auto TagComponentInvisibleRect = std::make_shared<dae::TagComponent>("InvisibleRect");
		auto CollidesWithCharacter = std::make_shared<dae::CollisionWithComponent>(Qbert);  
		auto CollisionResponse = std::make_shared<dae::CollsionResponse>();

		InvisibleRect->AddComponent(RectComponentInvisible);
		InvisibleRect->AddComponent(TagComponentInvisibleRect);
		InvisibleRect->AddComponent(CollidesWithCharacter);
		InvisibleRect->AddComponent(CollisionResponse);
		InvisibleRect->SetPosition(x + XOffset * index, Y + YOffset * index);

		scene.Add(InvisibleRect);

	}

	float x2{ 90 };
	float Y2{ 80 };
	float YOffset2{ 18 };
	float XOffset2{ -12 };


	for (int index = 0; index < 7; index++)
	{
		auto InvisibleRect = std::make_shared<dae::GameObject>();
		auto RectComponentInvisible = std::make_shared<dae::RectangleComponent>(10, 10);
		auto TagComponentInvisibleRect = std::make_shared<dae::TagComponent>("InvisibleRect");
		auto CollidesWithCharacter = std::make_shared<dae::CollisionWithComponent>(Qbert); 
		auto CollisionResponse = std::make_shared<dae::CollsionResponse>();  

		InvisibleRect->AddComponent(RectComponentInvisible);
		InvisibleRect->AddComponent(TagComponentInvisibleRect);
		InvisibleRect->AddComponent(CollidesWithCharacter);
		InvisibleRect->AddComponent(CollisionResponse);
		InvisibleRect->SetPosition(x2 + XOffset2 * index, Y2 + YOffset2 * index);

		scene.Add(InvisibleRect);
	}

	float x3{ 10 };
	float Y3{ 220 };
	float XOffset3{ 15 };

	for (int index = 0; index < 15; index++)
	{
		auto InvisibleRect = std::make_shared<dae::GameObject>();
		auto RectComponentInvisible = std::make_shared<dae::RectangleComponent>(13, 13); 
		auto TagComponentInvisibleRect = std::make_shared<dae::TagComponent>("InvisibleRect");
		auto CollidesWithCharacter = std::make_shared<dae::CollisionWithComponent>(Qbert);
		auto CollisionResponse = std::make_shared<dae::CollsionResponse>();

		InvisibleRect->AddComponent(RectComponentInvisible);
		InvisibleRect->AddComponent(TagComponentInvisibleRect);
		InvisibleRect->AddComponent(CollidesWithCharacter);
		InvisibleRect->AddComponent(CollisionResponse);
		InvisibleRect->SetPosition(x3 + XOffset3 * index, Y3);
		scene.Add(InvisibleRect);

	}
}

void CreateMap(dae::Scene& scene, std::vector<std::shared_ptr<dae::GameObject>>& CubesVector)
{
	int row{};
	int column{};


	float x{ 25 };
	float y{ 205 };
	int number{ 7 };
	int total{ number };


	bool minus1 = false;

	for (column = 0; column < total; column++)
	{

		if (minus1)
		{
			--number;
		}

		for (row = 0; row < number; row++)
		{
			minus1 = true;
			auto Cube = std::make_shared<dae::GameObject>();
			auto CubeRenderer = std::make_shared<dae::RenderComponent>(-2, true);
			auto CubeRectangle = std::make_shared<dae::RectangleComponent>(8, 10);   
			CubeRectangle->AddOffset(2, 0);
			CubeRenderer->SetTexture("cubes.png");
			CubeRenderer->SetDimension(0.3f);
			CubeRenderer->AddToVector(6, 2, 1, 0, dae::AnimationComponent::Type::loop, 0, 0);  
			CubeRenderer->AddToVector(6, 2, 1, 0, dae::AnimationComponent::Type::loop, 0, 1); 
			CubeRenderer->AddToVector(6, 2, 1, 0, dae::AnimationComponent::Type::loop, 0, 2); 
			CubeRenderer->AddToVector(6, 2, 1, 0, dae::AnimationComponent::Type::loop, 0, 3); 
			CubeRenderer->AddToVector(6, 2, 1, 0, dae::AnimationComponent::Type::loop, 0, 4); 
			CubeRenderer->AddToVector(6, 2, 1, 0, dae::AnimationComponent::Type::loop, 0, 5); 
			Cube->AddComponent(CubeRenderer);
			Cube->AddComponent(CubeRectangle);
			Cube->SetPosition(x + 23.f * row, y - 18.f * column);
			scene.Add(Cube);

			CubesVector.push_back(Cube);

		}
		x += 12.f;
	}
}


void Level2()
{

	std::vector < std::shared_ptr<dae::GameObject>> m_enemiesVector;


	auto& scene = dae::SceneManager::GetInstance().CreateScene("Level2");
	scene.SetId(4);

	std::vector<std::shared_ptr<dae::GameObject>> CubesVector;

	CreateMap(scene, CubesVector);

	//auto PinkDot = CreateRedDot(scene, m_enemiesVector, 2.0f, 1.4f, TypeOfAi::Allleft,"MovingDotsvariant.png");
	auto greenDot = CreateRedDot(scene, m_enemiesVector, 1.2f, 1.2f, TypeOfAi::LeftRight,"MovingDotsGreen.png");
//	auto RedDot = CreateRedDot(scene, m_enemiesVector, 1.7f, 1.7f, TypeOfAi::AllRight,"movingdots.png");
	auto RedDot2 = CreateRedDot(scene, m_enemiesVector, 0.7f, 0.7f, TypeOfAi::Allleft,"movingdots.png");
	auto PinkDot2 = CreateRedDot(scene, m_enemiesVector, 0.7f, 0.5f, TypeOfAi::RightLeft,"MovingDotsvariant.png");

	//CreateBottomRectEnemies(PinkDot, scene);
	CreateBottomRectEnemies(greenDot, scene);
	//CreateBottomRectEnemies(RedDot, scene);
	CreateBottomRectEnemies(RedDot2, scene);
	CreateBottomRectEnemies(PinkDot2, scene);







	auto Snake = CreateSnake(scene, m_enemiesVector);
	DrawInvisibleDotsmainSnake(Snake, scene);
	DrawButtonRectSnake(Snake, scene);

	float InitialPosX{ 98 };
	float InitialPosY{ 87 };

	auto Qbert = CreateQbert(scene, int(Level::Level2), InitialPosX, InitialPosY, CubesVector, m_enemiesVector);

	DrawInvisibleDotsmainLevel(Qbert, scene);
	DrawButtonRectMainLevel(Qbert, scene);

	ChangeToCube(scene, 5);


	DrawNumber2(scene, 1);
	PlayerText(scene);
	DrawDetails(scene);
	DisplayScore(scene);
	DisplayLives(scene);
	CreatePlatforms(Qbert, scene);


}



void Level3()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Level3");
	scene.SetId(6);

	std::vector<std::shared_ptr<dae::GameObject>> CubesVector;
	std::vector < std::shared_ptr<dae::GameObject>> m_enemiesVector;

	CreateMap(scene, CubesVector);



	auto PinkDot = CreateRedDot(scene, m_enemiesVector, 1.3f, 1.1f, TypeOfAi::Allleft,"MovingDotsvariant.png");
	auto greenDot = CreateRedDot(scene, m_enemiesVector, 1.2f, 1.2f, TypeOfAi::Allleft,"MovingDotsGreen.png");
	auto RedDot = CreateRedDot(scene, m_enemiesVector, 1.7f, 1.7f, TypeOfAi::AllRight,"movingdots.png");
	auto RedDot2 = CreateRedDot(scene, m_enemiesVector, 0.7f, 0.7f, TypeOfAi::AllRight,"movingdots.png");
	auto PinkDot2 = CreateRedDot(scene, m_enemiesVector, 1.3f, 1.2f, TypeOfAi::LeftRight,"MovingDotsvariant.png");
	auto PinkDot3 = CreateRedDot(scene, m_enemiesVector, 0.9f, 0.5f, TypeOfAi::RightLeft,"MovingDotsvariant.png");

	CreateBottomRectEnemies(PinkDot, scene);
	CreateBottomRectEnemies(greenDot, scene);
	CreateBottomRectEnemies(RedDot, scene);
	CreateBottomRectEnemies(RedDot2, scene);
	CreateBottomRectEnemies(PinkDot2, scene);
	CreateBottomRectEnemies(PinkDot3, scene);

	auto Snake = CreateSnake(scene, m_enemiesVector);
	DrawInvisibleDotsmainSnake(Snake, scene);
	DrawButtonRectSnake(Snake, scene);

	float InitialPosX{ 98 };
	float InitialPosY{ 87 };

	auto Qbert = CreateQbert(scene, int(Level::Level3), InitialPosX, InitialPosY, CubesVector, m_enemiesVector);

	DrawInvisibleDotsmainLevel(Qbert, scene);
	DrawButtonRectMainLevel(Qbert, scene);
	ChangeToCube(scene, 4);

	DrawNumber2(scene, 2);
	PlayerText(scene);
	DrawDetails(scene);
	DisplayScore(scene);
	DisplayLives(scene);
	CreatePlatforms(Qbert, scene);
}


void InputNameScene()
{

	auto& scene = dae::SceneManager::GetInstance().CreateScene("InputNameScene");

	auto& input2 = dae::InputManager::GetInstance();

	auto keyboard2{ input2.GetKeyboard() };


	std::vector<std::shared_ptr<dae::GameObject>> objects;

	char character = 'A';
	int index = 0;

	for (int columns = 0; columns < 3; columns++)
	{
		for (int rows = 0; rows < 9; rows++)
		{
			auto LetterGameObject = std::make_shared<dae::GameObject>();
			auto Renderer = std::make_shared<dae::RenderComponent>();
			auto pTextComponent = std::make_shared<dae::TextComponent>(Renderer, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 30));
			pTextComponent->SetColor({ 200,200,0 });
			LetterGameObject->AddComponent(pTextComponent);
			auto KeyBoardComponent = std::make_shared<dae::KeyBoardComponent>(character, LetterGameObject->GetComponent<dae::TextComponent>());
			KeyBoardComponent->m_index = ++index;
			LetterGameObject->AddComponent(Renderer);
			LetterGameObject->AddComponent(KeyBoardComponent);
			LetterGameObject->SetPosition(10, 10);
			LetterGameObject->SetPosition(20.f + 20.f * rows, 50.f + 20.f * columns);
			character++;
			if (rows == 0 && columns == 0)
			{
				KeyBoardComponent->m_IsActive = true;
			}
			scene.Add(LetterGameObject);
			objects.push_back(LetterGameObject);

		}

	}



	int currentTileActive = 0;



	std::unique_ptr<dae::Command> SetSceneCommand{ std::make_unique<dae::ChangeSelectionCommand>(objects,currentTileActive,dae::Direction::LEFT) };// one of when isntantiating a class 
	keyboard2->MapCommandToButton(SDL_SCANCODE_LEFT, std::move(SetSceneCommand), dae::ButtonState::Up);

	//will have to make it o
	SetSceneCommand = std::make_unique<dae::ChangeSelectionCommand>(objects, currentTileActive, dae::Direction::RIGHT);// one of when isntantiating a class 
	keyboard2->MapCommandToButton(SDL_SCANCODE_RIGHT, std::move(SetSceneCommand), dae::ButtonState::Up);

	SetSceneCommand = std::make_unique<dae::ChangeSelectionCommand>(objects, currentTileActive, dae::Direction::UP);// one of when isntantiating a class 
	keyboard2->MapCommandToButton(SDL_SCANCODE_UP, std::move(SetSceneCommand), dae::ButtonState::Up);

	SetSceneCommand = std::make_unique<dae::ChangeSelectionCommand>(objects, currentTileActive, dae::Direction::DOWN);// one of when isntantiating a class 
	keyboard2->MapCommandToButton(SDL_SCANCODE_DOWN, std::move(SetSceneCommand), dae::ButtonState::Up);













	//duplicate these 2 



	std::unique_ptr<dae::Command> SkipLevelsCommand{ std::make_unique<dae::LockInCommand>(objects) };// one of when isntantiating a class 
	keyboard2->MapCommandToButton(SDL_SCANCODE_RETURN, std::move(SkipLevelsCommand), dae::ButtonState::Up);


	//with enter 







	SetSceneCommand = std::make_unique<dae::NextSceneCommand>("ScoresScene", GameMode::Versus);
	keyboard2->MapCommandToButton(SDL_SCANCODE_5, std::move(SetSceneCommand), dae::ButtonState::Up);





	//create a game object with the component lihe the higscore that holds a static

	//add soudns to keyboard 

	//do theb platform and the the enemies 
	//and the highscore



	CreateButton(scene, " When you are ready press 5", 20, 140, SDL_Color{ 255,255,255,255 }, 30,"Empty");
	//  unno como el hud object que tenianuna estatiuca adentro 



	auto NameObject = std::make_shared<dae::GameObject>();
	auto pFrameRateRenderer = std::make_shared<dae::RenderComponent>();
	auto pTextComponent = std::make_shared<dae::TextComponent>(pFrameRateRenderer, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 30));
	auto playerNameComponent = std::make_shared<dae::DisplayNameComponent>(pTextComponent);
	playerNameComponent->m_IsName = true;
	pTextComponent->SetColor({ 255,200,0 });
	NameObject->AddComponent(pTextComponent);
	NameObject->AddComponent(playerNameComponent);
	NameObject->AddComponent(pFrameRateRenderer);
	NameObject->SetPosition(20, 200);
	scene.Add(NameObject);






}

void LoadCoOpScene()
{

	auto& scene = dae::SceneManager::GetInstance().CreateScene("CoOpScene");


	std::vector<std::shared_ptr<dae::GameObject>> CubesVector;
	std::vector < std::shared_ptr<dae::GameObject>> m_enemiesVector;
	CreateMap(scene, CubesVector);



	auto PinkDot = CreateRedDot(scene, m_enemiesVector, 2.0f, 1.4f, TypeOfAi::Allleft,"MovingDotsvariant.png");
	auto greenDot = CreateRedDot(scene, m_enemiesVector, 1.2f, 1.2f, TypeOfAi::LeftRight,"MovingDotsGreen.png");
	auto RedDot2 = CreateRedDot(scene, m_enemiesVector, 0.7f, 0.7f, TypeOfAi::Allleft,"movingdots.png");

	CreateBottomRectEnemies(PinkDot, scene);  //teleports them 
	CreateBottomRectEnemies(greenDot, scene);
	CreateBottomRectEnemies(RedDot2, scene);

	auto Snake = CreateSnake(scene, m_enemiesVector);
	DrawInvisibleDotsmainSnake(Snake, scene);  //for the 
	DrawButtonRectSnake(Snake, scene);


	float InitialPosX{ 26 };
	float InitialPosY{ 195 };

	//I renamed this to q bert   //set amount of livesa is equal to 7 

	auto Qbert1 = CreateQbert(scene, int(Level::Level1), InitialPosX, InitialPosY, CubesVector, m_enemiesVector);


	DrawInvisibleDotsmainLevel(Qbert1, scene); //collsio for the qbert 
	DrawButtonRectMainLevel(Qbert1, scene);


	float TopPosX{ 98 };
	float TopPoY{ 87 };


	//	I DUNNO IF I WANT TYE CODE IN THE COMPONENTS REPEATED 

	auto Qbert2 = std::make_shared<dae::GameObject>();
	Qbert2->SavePosition(TopPosX, TopPoY);
	auto QbertRenderer2 = std::make_shared<dae::RenderComponent>(-2, true);
	auto JumpComponent2 = std::make_shared<dae::JumpAnimationComponent>(); //FOR NOW NOT DOING ANYTHING
	auto RectComponent2 = std::make_shared<dae::RectangleComponent>(9, 10);
	auto TagQbertComponent2 = std::make_shared<dae::TagComponent>("Qbert");
	RectComponent2->SetWidthAndHeightCollidingRectangle(23, 23);
	RectComponent2->AddOffsetEnemiesCollidingRect(5, 5);
	auto TimerAndInputComponent2 = std::make_shared<dae::TimerAndInputComponent>();
	RectComponent2->AddOffset(-4, 10);
	auto Collider2 = std::make_shared<dae::CollisionComponent>(CubesVector, int(Level::Level1), m_enemiesVector);   //pass level    type of game 
	auto freeFallComponent2 = std::make_shared<dae::FreeFallComponent>();

	QbertRenderer2->SetTexture("qbert.png");
	QbertRenderer2->SetDimension(0.45f);       //was 0.5     
	QbertRenderer2->AddToVector(4, 2, 2, 5, dae::AnimationComponent::Type::loop, 1, 0);
	QbertRenderer2->AddToVector(4, 2, 2, 5, dae::AnimationComponent::Type::loop, 1, 1);
	QbertRenderer2->AddToVector(4, 2, 2, 5, dae::AnimationComponent::Type::loop, 1, 2);
	QbertRenderer2->AddToVector(4, 2, 2, 5, dae::AnimationComponent::Type::loop, 1, 3);

	Qbert2->AddComponent(RectComponent2);
	Qbert2->AddComponent(JumpComponent2);
	Qbert2->AddComponent(Collider2);
	Qbert2->AddComponent(QbertRenderer2);
	Qbert2->AddComponent(freeFallComponent2);
	Qbert2->AddComponent(TimerAndInputComponent2);
	Qbert2->AddComponent(TagQbertComponent2);
	Qbert2->SetPosition(170, 195);
	scene.Add(Qbert2);
	scene.AddPlayer2(Qbert2);


	auto CurseQbert = std::make_shared<dae::GameObject>();
	auto CurseQbertRenderer = std::make_shared<dae::RenderComponent>(-2, true);
	auto CurseQbertComponent = std::make_shared<dae::CurseQbertComponent>(Qbert2);
	CurseQbertRenderer->SetTexture("one.png");
	CurseQbertRenderer->SetDimension(0.2f);         //HAVE TWO players so they get hidden when they use theb platform
	CurseQbertRenderer->AddToVector(2, 1, 1, 0, dae::AnimationComponent::Type::loop, 0, 0);
	CurseQbert->AddComponent(CurseQbertRenderer);
	CurseQbert->AddComponent(CurseQbertComponent);
	CurseQbert->SetPosition(98, 70);
	scene.Add(CurseQbert);




	DrawInvisibleDotsmainLevel(Qbert2, scene);
	DrawButtonRectMainLevel(Qbert2, scene);


	ChangeToCube(scene, 1);
	DrawNumber2(scene, 2);
	PlayerText(scene);
	DrawDetails(scene);
	DisplayScore(scene);
	DisplayLives(scene);


	//both q bertrs
	CreatePlatforms(Qbert1, scene);
	CreatePlatforms(Qbert2, scene);


}

void LoadScoresScene()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("ScoresScene");  //creaate scene   
	//CreateButton(scene, "Highest Score",70,30);


	CreateButton(scene, " Max Scores ", 50, 20, SDL_Color{ 255,255,255,255 }, 50,"");





	//can have boolean that lets decide which static name score or highes score that way we save code 

	auto NameObject = std::make_shared<dae::GameObject>();
	auto pFrameRateRenderer = std::make_shared<dae::RenderComponent>();
	auto pTextComponent = std::make_shared<dae::TextComponent>(pFrameRateRenderer, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25));
	auto playerNameComponent = std::make_shared<dae::DisplayNameComponent>(pTextComponent);
	playerNameComponent->m_IsName = true;
	pTextComponent->SetColor({ 255,200,0 });
	NameObject->AddComponent(pTextComponent);
	NameObject->AddComponent(playerNameComponent);
	NameObject->AddComponent(pFrameRateRenderer);
	NameObject->SetPosition(10, 100);
	scene.Add(NameObject);



	auto PlayerScore = std::make_shared<dae::GameObject>();
	auto PlayerScoreRenderer = std::make_shared<dae::RenderComponent>();
	auto pTextComponent2 = std::make_shared<dae::TextComponent>(PlayerScoreRenderer, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25));
	auto playerScoreComponent = std::make_shared<dae::DisplayNameComponent>(pTextComponent2);
	playerScoreComponent->m_IsScore = true;  //change 
	pTextComponent2->SetColor({ 255,200,0 });
	PlayerScore->AddComponent(pTextComponent2);
	PlayerScore->AddComponent(playerScoreComponent);
	PlayerScore->AddComponent(PlayerScoreRenderer);
	PlayerScore->SetPosition(160, 100);
	scene.Add(PlayerScore);



	auto HighesScore = std::make_shared<dae::GameObject>();
	auto HighesScoreRenderer = std::make_shared<dae::RenderComponent>();
	auto pTextComponent3 = std::make_shared<dae::TextComponent>(HighesScoreRenderer, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 25));
	auto playerScoreComponen3 = std::make_shared<dae::DisplayNameComponent>(pTextComponent3);
	playerScoreComponen3->m_IsHighestScore = true;  //change 
	pTextComponent2->SetColor({ 255,200,0 });
	HighesScore->AddComponent(pTextComponent3);
	HighesScore->AddComponent(playerScoreComponen3);
	HighesScore->AddComponent(HighesScoreRenderer);
	HighesScore->SetPosition(30, 60);
	scene.Add(HighesScore);


}

void LoadVersusMode()
{

	auto& scene = dae::SceneManager::GetInstance().CreateScene("VersusMode");
	std::vector < std::shared_ptr<dae::GameObject>> m_enemiesVector;
	std::vector < std::shared_ptr<dae::GameObject>> m_enemiesSnake;

	std::vector<std::shared_ptr<dae::GameObject>> CubesVector;
	std::vector<std::shared_ptr<dae::GameObject>> CubesVectorEmpty;


	//I set the lives to 7 
	CreateMap(scene, CubesVector);
	auto PinkDot = CreateRedDot(scene, m_enemiesVector, 2.0f, 1.4f, TypeOfAi::Allleft,"MovingDotsvariant.png");

	
	CreateBottomRectEnemies(PinkDot, scene);
	
	auto Snake = std::make_shared<dae::GameObject>();
	Snake->SavePosition(96, 112);
	auto SnakeRenderer = std::make_shared<dae::RenderComponent>(-2, true);
	auto RectComponentSnake = std::make_shared<dae::RectangleComponent>(20, 20);
	auto TagComponentSnake = std::make_shared<dae::TagComponent>("SnakePlayer");

	//if tag is snalke player 
	RectComponentSnake->AddOffset(3, 25);
	auto TimerAndInputComponentSnake = std::make_shared<dae::TimerAndInputComponent>();
	auto ColliderSnake = std::make_shared<dae::CollisionComponent>(CubesVector, int(Level::Level1), m_enemiesSnake);   //is being updated 
	auto freeFallComponentSnake = std::make_shared<dae::FreeFallComponent>();
	auto JumpAnimationSnake = std::make_shared<dae::JumpAnimationComponent>();
	SnakeRenderer->SetTexture("jumpingSnake.png");
	SnakeRenderer->SetDimension(0.4f);
	SnakeRenderer->AddToVector(4, 2, 2, 1, dae::AnimationComponent::Type::loop, 0, 0);  //right
	SnakeRenderer->AddToVector(4, 2, 2, 1, dae::AnimationComponent::Type::loop, 0, 1);  //right
	SnakeRenderer->AddToVector(4, 2, 2, 1, dae::AnimationComponent::Type::loop, 0, 2);  //right
	SnakeRenderer->AddToVector(4, 2, 2, 1, dae::AnimationComponent::Type::loop, 0, 3);  //right

	Snake->AddComponent(SnakeRenderer);
	Snake->AddComponent(RectComponentSnake);
	Snake->AddComponent(TimerAndInputComponentSnake);
	Snake->AddComponent(ColliderSnake);
	Snake->AddComponent(freeFallComponentSnake);
	Snake->AddComponent(JumpAnimationSnake);
	Snake->AddComponent(TagComponentSnake);
	Snake->SetPosition(96, 112);
	scene.Add(Snake);
	scene.AddEnemy(Snake);
	m_enemiesVector.push_back(Snake);
	DrawInvisibleDotsmainLevel(Snake, scene);   //for invisible dots   //later will decrease lives 
	DrawButtonRectMainLevel(Snake, scene);  //for invisible rect and get teleported


	float InitialPosX{ 98 };
	float InitialPosY{ 87 };

	auto Qbert = CreateQbert(scene, int(Level::Level1), InitialPosX, InitialPosY, CubesVector, m_enemiesVector);


	DrawInvisibleDotsmainLevel(Qbert, scene);
	DrawButtonRectMainLevel(Qbert, scene);


	ChangeToCube(scene, 1);
	DrawNumber2(scene, 2);
	PlayerText(scene);
	DrawDetails(scene);
	DisplayLives(scene);
	DisplayScore(scene);
	CreatePlatforms(Qbert, scene);

}

void load()
{
#if _DEBUG
	dae::Audio::RegisterService(std::make_unique<dae::SDL_SoundSystem>());
#else
	dae::Audio::RegisterService(std::make_unique<dae::SDL_SoundSystem>());
	//set the isntance of Audio as SDL sOUND 


#endif
	dae::SoundSystem& audio{ dae::Audio::Get() };   //gets a  sdl_soundsystem //buy since that is also a SounDssYSTEM it is oki 

	audio.AddSound("Background.mp3", s_MenuMusicId, true);
	audio.Play(s_GameSoundId, 0.5f, 100);

	audio.AddSound("ActStart.mp3", s_GameSoundId, true);   //is music  was true
	//played when hetting key

	audio.Preload(s_QbertJump);
	audio.AddSound("qbert_jump.mp3", s_QbertJump, true);   //ais solo es una vez 


	audio.Preload(s_QbertCurse);  //preload
	audio.AddSound("qbert_fall.mp3", s_QbertCurse, true);


	audio.Preload(s_KeyBoardkeyMusic);
	audio.AddSound("keyboard-spacebar-hit-101812.mp3", s_KeyBoardkeyMusic, true);

	audio.Preload(s_QbertDead);
	audio.AddSound("qbert_swearing_3.mp3", s_QbertDead, true);

	audio.Preload(s_PlatformSound);
	audio.AddSound("disk_lift.mp3", s_PlatformSound, false);




	LoadMenuScene();

	Level1();


	//Level1TutoriaL();
	//Level2TutoriaL();
	//Level3TutoriaL();

	//Level1();   
	//Level2();
	//Level3();


	LoadCoOpScene();
	LoadVersusMode();
	LoadScoresScene();
	InputNameScene();

	dae::SceneManager::GetInstance().SetCurrentScene("MenuScene");
}


int main(int, char* [])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);  //load all scenes at once 
	return 0;
}




std::shared_ptr<dae::GameObject> CreatePinkDot(dae::Scene& scene, std::vector<std::shared_ptr<dae::GameObject>>& enemiesvector, float TimeToUpdate, float TimeOnAir, TypeOfAi ai)
{

	auto movingDots = std::make_shared<dae::GameObject>();
	auto MovingDotsRenderer = std::make_shared<dae::RenderComponent>(-2, true);
	auto EnemyJumpComponent = std::make_shared<dae::EnemyJumpComponent>(TimeToUpdate, 0.f, ai, TimeOnAir);
	auto EnemyRectComponentDot1 = std::make_shared<dae::RectangleComponent>(20, 20);
	EnemyRectComponentDot1->AddOffset(3, 0);
	MovingDotsRenderer->SetTexture("movingdots.png");
	MovingDotsRenderer->SetDimension(0.3f);       
	MovingDotsRenderer->AddToVector(3, 2, 2, 1, dae::AnimationComponent::Type::loop, 1, 0);  //right
	movingDots->AddComponent(MovingDotsRenderer);
	movingDots->AddComponent(EnemyJumpComponent);
	movingDots->AddComponent(EnemyRectComponentDot1);
	movingDots->SetPosition(90, 108);
	movingDots->SavePosition(90, 108);

	scene.Add(movingDots);

	enemiesvector.push_back(movingDots);

	return movingDots;

}

std::shared_ptr<dae::GameObject> CreateGreenDot(dae::Scene& scene, std::vector<std::shared_ptr<dae::GameObject>>& enemiesvector, float TimeToUpdate, float TimeOnAir, TypeOfAi ai)
{


	auto movingDots2 = std::make_shared<dae::GameObject>();
	auto MovingDotsRenderer2 = std::make_shared<dae::RenderComponent>(-2, true);
	auto EnemyJumpComponentDot2 = std::make_shared<dae::EnemyJumpComponent>(TimeToUpdate, 0.f, ai, TimeOnAir);
	auto EnemyRectComponentDot2 = std::make_shared<dae::RectangleComponent>(20, 20);
	EnemyRectComponentDot2->AddOffset(2, 7);
	MovingDotsRenderer2->SetTexture("movingdots.png");
	MovingDotsRenderer2->SetDimension(0.4f);         
	MovingDotsRenderer2->AddToVector(3, 2, 2, 2, dae::AnimationComponent::Type::loop, 1, 1);  
	movingDots2->AddComponent(MovingDotsRenderer2);
	movingDots2->AddComponent(EnemyJumpComponentDot2);
	movingDots2->AddComponent(EnemyRectComponentDot2);
	movingDots2->SetPosition(88, 105);
	movingDots2->SavePosition(88, 105);
	scene.Add(movingDots2);
	enemiesvector.push_back(movingDots2);

	return movingDots2;


}

std::shared_ptr<dae::GameObject> CreateRedDot(dae::Scene& scene, std::vector<std::shared_ptr<dae::GameObject>>& enemiesvector, float TimeToUpdate, float TimeOnAir, TypeOfAi ai,std::string FileName)
{

	//movingdots.png

	auto movingDots3 = std::make_shared<dae::GameObject>();
	auto MovingDotsRenderer3 = std::make_shared<dae::RenderComponent>(-2, true);
	auto EnemyJumpComponentDot3 = std::make_shared<dae::EnemyJumpComponent>(TimeToUpdate, 0.f, ai, TimeOnAir);
	auto EnemyRectComponentDot3 = std::make_shared<dae::RectangleComponent>(20, 20);

	MovingDotsRenderer3->SetTexture(FileName);
	MovingDotsRenderer3->SetDimension(0.3f);        
	MovingDotsRenderer3->AddToVector(3, 2, 2, 2, dae::AnimationComponent::Type::loop, 1, 2);
	movingDots3->AddComponent(MovingDotsRenderer3);
	movingDots3->AddComponent(EnemyRectComponentDot3);
	movingDots3->AddComponent(EnemyJumpComponentDot3);
	movingDots3->SetPosition(112, 109);
	movingDots3->SavePosition(112, 109);
	scene.Add(movingDots3);

	enemiesvector.push_back(movingDots3);

	return movingDots3;


}

std::shared_ptr<dae::GameObject> CreateSnake(dae::Scene& scene, std::vector<std::shared_ptr<dae::GameObject>>& enemiesvector)
{


	auto Snake = std::make_shared<dae::GameObject>();
	auto SnakeRenderer = std::make_shared<dae::RenderComponent>(-2, true);
	auto EnemyJumpComponentSnake = std::make_shared<dae::EnemyJumpComponent>(2.f, 0.f, TypeOfAi::Snake, 1.4f);
	auto FreeFallSnake = std::make_shared<dae::FreeFallComponent>();
	auto TagComponentSnake = std::make_shared<dae::TagComponent>("SnakeAi");
	auto EnemyRectComponentSnake = std::make_shared<dae::RectangleComponent>(20, 20);
	EnemyRectComponentSnake->AddOffset(3, 25);
	SnakeRenderer->SetTexture("snake.png");
	SnakeRenderer->SetDimension(0.41f);
	SnakeRenderer->AddToVector(2, 2, 2, 1, dae::AnimationComponent::Type::loop, 1, 0);
	SnakeRenderer->AddToVector(2, 2, 2, 1, dae::AnimationComponent::Type::loop, 1, 1);
	Snake->AddComponent(SnakeRenderer);
	Snake->AddComponent(EnemyJumpComponentSnake);
	Snake->AddComponent(EnemyRectComponentSnake);
	Snake->AddComponent(FreeFallSnake);
	Snake->AddComponent(TagComponentSnake);
	Snake->SetPosition(87, 133);
	Snake->SavePosition(87, 133);
	scene.Add(Snake);
	enemiesvector.push_back(Snake);



	return Snake;
}

std::shared_ptr<dae::GameObject> CreateQbert(dae::Scene& scene, int leve, float xpos, float ypos, std::vector<std::shared_ptr<dae::GameObject>>& cubesVector, std::vector<std::shared_ptr<dae::GameObject>>& enemies)
{


	float TopPosX{ 98 };
	float TopPoY{ 87 };     //


	auto Qbert = std::make_shared<dae::GameObject>();
	Qbert->SavePosition(TopPosX, TopPoY);
	auto QbertRenderer = std::make_shared<dae::RenderComponent>(-2, true);
	auto JumpComponent = std::make_shared<dae::JumpAnimationComponent>(); //FOR NOW NOT DOING ANYTHING
	auto RectComponent = std::make_shared<dae::RectangleComponent>(9, 10);    //was 20 20
	auto TagQbertComponent = std::make_shared<dae::TagComponent>("Qbert");
	RectComponent->SetWidthAndHeightCollidingRectangle(23, 23);
	RectComponent->AddOffsetEnemiesCollidingRect(5, 5);
	//asdsfdss
	auto TimerAndInputComponent = std::make_shared<dae::TimerAndInputComponent>();
	RectComponent->AddOffset(-4, 10);   //was 5 5
	auto Collider = std::make_shared<dae::CollisionComponent>(cubesVector, leve, enemies);   //pass level    type of game 
	auto freeFallComponent = std::make_shared<dae::FreeFallComponent>();
	QbertRenderer->SetTexture("qbert.png");
	QbertRenderer->SetDimension(0.45f);       //was 0.5     
	//QbertRenderer->SetDimension(0.1f);       //was 0.5     
	QbertRenderer->AddToVector(4, 2, 2, 5, dae::AnimationComponent::Type::loop, 1, 0);
	QbertRenderer->AddToVector(4, 2, 2, 5, dae::AnimationComponent::Type::loop, 1, 1);
	QbertRenderer->AddToVector(4, 2, 2, 5, dae::AnimationComponent::Type::loop, 1, 2);
	QbertRenderer->AddToVector(4, 2, 2, 5, dae::AnimationComponent::Type::loop, 1, 3);

	Qbert->AddComponent(RectComponent);
	Qbert->AddComponent(JumpComponent);
	Qbert->AddComponent(Collider);
	Qbert->AddComponent(QbertRenderer);
	Qbert->AddComponent(freeFallComponent);
	Qbert->AddComponent(TimerAndInputComponent);
	Qbert->AddComponent(TagQbertComponent);
	Qbert->SetPosition(xpos, ypos);
	scene.Add(Qbert);
	scene.AddPlayer(Qbert);

	auto CurseQbert = std::make_shared<dae::GameObject>();
	auto CurseQbertRenderer = std::make_shared<dae::RenderComponent>(-2, true);
	auto CurseQbertComponent = std::make_shared<dae::CurseQbertComponent>(Qbert);
	CurseQbertRenderer->SetTexture("one.png");
	CurseQbertRenderer->SetDimension(0.2f);         //HAVE TWO players so they get hidden when they use theb platform
	CurseQbertRenderer->AddToVector(2, 1, 1, 0, dae::AnimationComponent::Type::loop, 0, 0);
	CurseQbert->AddComponent(CurseQbertRenderer);
	CurseQbert->AddComponent(CurseQbertComponent);
	CurseQbert->SetPosition(98, 70);
	scene.Add(CurseQbert);


	return Qbert;


}

std::shared_ptr<dae::GameObject> CreateQbertTutorial(dae::Scene& scene, int leve, float xpos, float ypos, std::vector<std::shared_ptr<dae::GameObject>>& cubesVector, std::vector<std::shared_ptr<dae::GameObject>>& enemies)
{

	auto Qbert = std::make_shared<dae::GameObject>();
	auto QbertRenderer = std::make_shared<dae::RenderComponent>(-2, true);
	auto JumpComponent = std::make_shared<dae::JumpAnimationComponent>(); //FOR NOW NOT DOING ANYTHING
	auto RectComponent = std::make_shared<dae::RectangleComponent>(20, 20);    //was 20 20
	auto TimerAndInputComponent = std::make_shared<dae::TimerAndInputComponent>();
	auto TagQbertComponent = std::make_shared<dae::TagComponent>("Qbert");
	RectComponent->AddOffset(-4, 10);   //was 5 5
	auto Collider = std::make_shared<dae::CollisionComponent>(cubesVector, leve, enemies);   //pass level    type of game 
	auto freeFallComponent = std::make_shared<dae::FreeFallComponent>();

	QbertRenderer->SetTexture("qbert.png");
	QbertRenderer->SetDimension(0.45f);       //was 0.5     
	//QbertRenderer->SetDimension(0.1f);       //was 0.5     
	QbertRenderer->AddToVector(4, 2, 2, 5, dae::AnimationComponent::Type::loop, 1, 0);
	QbertRenderer->AddToVector(4, 2, 2, 5, dae::AnimationComponent::Type::loop, 1, 1);
	QbertRenderer->AddToVector(4, 2, 2, 5, dae::AnimationComponent::Type::loop, 1, 2);
	QbertRenderer->AddToVector(4, 2, 2, 5, dae::AnimationComponent::Type::loop, 1, 3);

	Qbert->AddComponent(RectComponent);
	Qbert->AddComponent(JumpComponent);
	Qbert->AddComponent(Collider);
	Qbert->AddComponent(QbertRenderer);
	Qbert->AddComponent(freeFallComponent);
	Qbert->AddComponent(TimerAndInputComponent);
	Qbert->AddComponent(TagQbertComponent);
	Qbert->SetPosition(xpos, ypos);
	scene.Add(Qbert);
	scene.AddPlayer(Qbert);


	return Qbert;
}

std::shared_ptr<dae::GameObject> CreateButton(dae::Scene& scene, const std::string& message, float x, float y, const SDL_Color& color, int size, const std::string & LevelName)
{



	auto TextGameObject = std::make_shared<dae::GameObject>();
	auto RenderComponentforText = std::make_shared<dae::RenderComponent>(-1, false);
	TextGameObject->AddComponent(RenderComponentforText);
	auto TextComponent = std::make_shared<dae::TextComponent>(RenderComponentforText);
	auto SaveLevelComponent = std::make_shared<dae::SaveLevelComponent>(LevelName);

	TextComponent->SetFont(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", size));
	TextComponent->SetColor(color);
	TextComponent->SetTextToTexture(message);
	TextGameObject->AddComponent(TextComponent);
	TextGameObject->AddComponent(SaveLevelComponent);
	TextGameObject->SetPosition(x, y);

	scene.Add(TextGameObject);

	return TextGameObject;


}
void LevelText(int index, dae::Scene& scene)
{

	auto LevelText = std::make_shared<dae::GameObject>();
	auto LevelTextRenderer = std::make_shared<dae::RenderComponent>(-2, true);
	LevelTextRenderer->SetTexture("level.png");
	LevelTextRenderer->SetDimension(1.8f);         //HAVE TWO players so they get hidden when they use theb platform
	LevelTextRenderer->AddToVector(3, 1, 0, 0, dae::AnimationComponent::Type::loop, 0, index);  //right
	LevelText->AddComponent(LevelTextRenderer);
	LevelText->SetPosition(25, 140);
	scene.Add(LevelText);



}

void LevelText2(int index, dae::Scene& scene)
{
	auto LevelText = std::make_shared<dae::GameObject>();
	auto LevelTextRenderer = std::make_shared<dae::RenderComponent>(-2, true);
	LevelTextRenderer->SetTexture("level.png");
	LevelTextRenderer->SetDimension(0.2f);         //HAVE TWO players so they get hidden when they use theb platform
	LevelTextRenderer->AddToVector(3, 1, 0, 0, dae::AnimationComponent::Type::loop, 0, index);  //right
	LevelText->AddComponent(LevelTextRenderer);
	LevelText->SetPosition(25, 180);
	scene.Add(LevelText);
}

void DrawNumber2(dae::Scene& scene, int index)
{

	auto NumberText = std::make_shared<dae::GameObject>();
	auto NumberTextRenderer = std::make_shared<dae::RenderComponent>(-2, true);
	NumberTextRenderer->SetTexture("numbersOneColumn.png");
	NumberTextRenderer->SetDimension(0.2f);       //was 0.5     
	NumberTextRenderer->AddToVector(3, 1, 1, 0, dae::AnimationComponent::Type::loop, 0, index);

	NumberText->AddComponent(NumberTextRenderer);

	NumberText->SetPosition(205, 57);
	scene.Add(NumberText);

}

std::vector<std::shared_ptr<dae::GameObject>>AddTutorialMap(dae::Scene& scene)
{
	std::vector<std::shared_ptr<dae::GameObject>> CubesVector;
	int row{};
	int column{};


	float x{ 70 };
	float y{ 105 };
	int number{ 3 };
	int total{ number };


	bool minus1 = false;

	for (column = 0; column < total; column++)
	{

		if (minus1)
		{
			--number;
		}

		for (row = 0; row < number; row++)
		{

			if (row == 0 && column == 0 || row == 2 && column == 0) continue;

			minus1 = true;
			auto Cube = std::make_shared<dae::GameObject>();
			auto CubeRenderer = std::make_shared<dae::RenderComponent>(-2, true);
			auto CubeRectangle = std::make_shared<dae::RectangleComponent>(10, 10);
			CubeRectangle->AddOffset(8, 2);
			//add offset


			CubeRenderer->SetTexture("cubes.png");
			CubeRenderer->SetDimension(0.3f);
			CubeRenderer->AddToVector(6, 2, 1, 0, dae::AnimationComponent::Type::loop, 0, 0);  //right   
			CubeRenderer->AddToVector(6, 2, 1, 0, dae::AnimationComponent::Type::loop, 0, 1);  //right
			CubeRenderer->AddToVector(6, 2, 1, 0, dae::AnimationComponent::Type::loop, 0, 2);  //right
			CubeRenderer->AddToVector(6, 2, 1, 0, dae::AnimationComponent::Type::loop, 0, 3);  //right
			CubeRenderer->AddToVector(6, 2, 1, 0, dae::AnimationComponent::Type::loop, 0, 4);  //right
			CubeRenderer->AddToVector(6, 2, 1, 0, dae::AnimationComponent::Type::loop, 0, 5);  //right
			Cube->AddComponent(CubeRenderer);
			Cube->AddComponent(CubeRectangle);
			Cube->SetPosition(x + 23.f * row, y - 18.f * column);

			scene.Add(Cube);

			CubesVector.push_back(Cube);

		}
		x += 12.f;
	}

	return CubesVector;

}
