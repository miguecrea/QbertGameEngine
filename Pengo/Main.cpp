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
#include"AiComponent.h"
#include"GameManagerComponent.h"
#include"Tags.h"
#include"EnemySpawner.h"


std::shared_ptr<dae::GameObject> CreateButton(dae::Scene& scene, const std::string& message, float x, float y, const SDL_Color& color, int size,const std::string & SaveLevelComponent);
std::shared_ptr<dae::GameObject> CreatePengoPlayer(dae::Scene & scene, float X, float Y,bool IsPlayerOne = true);
std::shared_ptr<dae::GameObject> CreateMap(dae::Scene& scene, std::shared_ptr<dae::GameObject> PengoGameObject, const std::string& MapFileName, int numberEnmies,std::shared_ptr<dae::GameObject> player2);
void DisplayLives(dae::Scene& scene,std::shared_ptr<dae::GameObject> & gameObject)
{
	auto PlayerScore = std::make_shared<dae::GameObject>();
	auto PlayerScoreRenderer = std::make_shared<dae::RenderComponent>();
	auto pTextComponent2 = std::make_shared<dae::TextComponent>(PlayerScoreRenderer, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24));
	auto playerScoreComponent = std::make_shared<dae::DisplayNameComponent>(pTextComponent2,gameObject);
	playerScoreComponent->m_IsLives = true;  //change 
	pTextComponent2->SetColor({ 0,255,255 });
	PlayerScore->AddComponent(pTextComponent2);
	PlayerScore->AddComponent(playerScoreComponent);
	PlayerScore->AddComponent(PlayerScoreRenderer);
	PlayerScore->SetPosition(150, 10);
	scene.Add(PlayerScore);
}
void DisplayScore(dae::Scene & scene,std::shared_ptr<dae::GameObject> & gameObject)
{
	auto PlayerScore = std::make_shared<dae::GameObject>();
	auto PlayerScoreRenderer = std::make_shared<dae::RenderComponent>();
	auto pTextComponent2 = std::make_shared<dae::TextComponent>(PlayerScoreRenderer, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24));
	auto playerScoreComponent = std::make_shared<dae::DisplayNameComponent>(pTextComponent2,gameObject);
	playerScoreComponent->m_IsScore = true;  //change 
	pTextComponent2->SetColor({ 255,0,0,255});
	PlayerScore->AddComponent(pTextComponent2);
	PlayerScore->AddComponent(playerScoreComponent);
	PlayerScore->AddComponent(PlayerScoreRenderer);
	PlayerScore->SetPosition(10, 10);
	scene.Add(PlayerScore);
}
std::shared_ptr<dae::GameObject> CreateEnemyManager(std::shared_ptr<dae::GameObject>& MapGameObject, std::vector<std::shared_ptr<dae::GameObject>>& Tiles, std::shared_ptr<dae::GameObject>& PengoGameObject, dae::Scene& scene, const std::string filename);


void  LoadMenuScene()
{
	auto & MenuScene = dae::SceneManager::GetInstance().CreateScene(MENU_SCENE);
	auto& input2 = dae::InputManager::GetInstance();

	auto controller = input2.AddController();
	auto keyboard{ input2.GetKeyboard() };


	std::unique_ptr<dae::Command> SetSceneCommand{ std::make_unique<dae::NextSceneCommand>(SINGLE_PLAYER_SCENE,GameMode::SinglePlayer) };// one of when isntantiating a class 
	keyboard->MapCommandToButton(SDL_SCANCODE_1, std::move(SetSceneCommand), dae::ButtonState::Up);


	std::unique_ptr<dae::Command> SkipLevelsCommand{ std::make_unique<dae::SkipLevelsCommand>() };// one of when isntantiating a class 
	keyboard->MapCommandToButton(SDL_SCANCODE_F1, std::move(SkipLevelsCommand), dae::ButtonState::Up);


	SetSceneCommand = std::make_unique<dae::NextSceneCommand>(CO_OP_SCENE, GameMode::Coop);
	keyboard->MapCommandToButton(SDL_SCANCODE_2, std::move(SetSceneCommand), dae::ButtonState::Up);

	SetSceneCommand = std::make_unique<dae::NextSceneCommand>(VERSUS_MODE, GameMode::Versus);
	keyboard->MapCommandToButton(SDL_SCANCODE_3, std::move(SetSceneCommand), dae::ButtonState::Up);

	SetSceneCommand = std::make_unique<dae::ToggleMuteCommand>();  //mute
	keyboard->MapCommandToButton(SDL_SCANCODE_9, std::move(SetSceneCommand), dae::ButtonState::Up);


	auto MapGameObject = std::make_shared<dae::GameObject>();
	auto MapRender = std::make_shared<dae::RenderComponent>(-1, false); 
	MapRender->SetTexture("MIGUEL_BackGroundPengo.png");
	MapRender->SetDimension(3.f);
	MapGameObject->AddComponent(MapRender);
	MapGameObject->SetPosition(0,0);
	MenuScene.Add(MapGameObject);

	

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
	


	std::unique_ptr<dae::ChangeModeCommand> ChangeMode = std::make_unique<dae::ChangeModeCommand>(TextGameObjects);
	std::unique_ptr<dae::OpenLevelCommand> OpenLevelCommand = std::make_unique<dae::OpenLevelCommand>(TextGameObjects, ChangeMode.get());

	controller->MapCommandToThumbstick(dae::Controller::ControllerThumbsticks::LeftThumbstick,std::move(ChangeMode));
	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonA,std::move(OpenLevelCommand),dae::ButtonState::Up);


	


}
void Level1()
{

	auto & scene = dae::SceneManager::GetInstance().CreateScene(SINGLE_PLAYER_SCENE);
	scene.SetId(1);

	std::vector <std::shared_ptr<dae::GameObject>> m_GameObjects;
	CreateBackGround(scene);

	auto PengoGameObject = CreatePengoPlayer(scene,100.f,100.f);

	auto MapGameObject = CreateMap(scene, PengoGameObject, "../Data/Map1.txt",2,nullptr);
	auto MapComponent = MapGameObject->GetComponent<dae::MapComponent>();

	auto Tiles  = MapComponent->GetTiles();
	Tiles.push_back(PengoGameObject);

	DisplayScore(scene,MapGameObject);
	DisplayLives(scene,PengoGameObject);
	CreateEnemyManager(MapGameObject, Tiles, PengoGameObject, scene, "MIGUEL_Enemy_RED.png");

}






void Level2()
{

	auto & scene = dae::SceneManager::GetInstance().CreateScene(LEVEL_2);
	scene.SetId(2);

	std::vector <std::shared_ptr<dae::GameObject>> m_GameObjects;
	CreateBackGround(scene);

	//////////////////////////////////////////////////////////
	auto PengoGameObject = CreatePengoPlayer(scene,100.f,100.f);

	auto MapGameObject = CreateMap(scene, PengoGameObject, "../Data/Map2.txt",4,nullptr);
	auto MapComponent = MapGameObject->GetComponent<dae::MapComponent>();

	auto Tiles = MapComponent->GetTiles();
	Tiles.push_back(PengoGameObject);

	DisplayScore(scene, MapGameObject);
	DisplayLives(scene, PengoGameObject);


	CreateEnemyManager(MapGameObject, Tiles, PengoGameObject, scene, "MIGUEL_Enemy_YELLOW.png");
	


}
void Level3()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene(LEVEL_3);
	scene.SetId(3);


	std::vector <std::shared_ptr<dae::GameObject>> m_GameObjects;
	CreateBackGround(scene);

	//////////////////////////////////////////////////////////
	auto PengoGameObject = CreatePengoPlayer(scene,100.f,100.f);

	auto MapGameObject = CreateMap(scene, PengoGameObject, "../Data/Map3.txt", 6,nullptr);
	auto MapComponent = MapGameObject->GetComponent<dae::MapComponent>();

	auto Tiles = MapComponent->GetTiles();
	Tiles.push_back(PengoGameObject);

	DisplayScore(scene, MapGameObject);
	DisplayLives(scene, PengoGameObject);

	CreateEnemyManager(MapGameObject, Tiles, PengoGameObject, scene,"Enemy.png");

	
}

void InputNameScene()
{

	auto& scene = dae::SceneManager::GetInstance().CreateScene(INPUT_NAME_SCENE);

	auto& input2 = dae::InputManager::GetInstance();

	auto keyboard2{ input2.GetKeyboard() };


	std::vector<std::shared_ptr<dae::GameObject>> objects;

	char character = 'A';
	int index = 0;



	float TileSize{ 60.f };
	float InitialPosX{30.f};
	float InitialPosY{90.f};
	float ROWS{ 3 };
	float COLUMN{ 9 };
	for (int columns = 0; columns < ROWS; columns++)
	{
		for (int rows = 0; rows < COLUMN; rows++)
		{
			auto LetterGameObject = std::make_shared<dae::GameObject>();
			auto Renderer = std::make_shared<dae::RenderComponent>();
			auto pTextComponent = std::make_shared<dae::TextComponent>(Renderer, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 30));
			pTextComponent->SetColor({ 200,200,0 });
	 
			LetterGameObject->AddComponent(pTextComponent);
			auto KeyBoardComponent = std::make_shared<dae::KeyBoardComponent>(character, LetterGameObject->GetComponent<dae::TextComponent>(),TileSize);
			KeyBoardComponent->m_index = ++index;
			LetterGameObject->AddComponent(Renderer);
			LetterGameObject->AddComponent(KeyBoardComponent);
			LetterGameObject->SetPosition(InitialPosX + TileSize * rows, InitialPosY + TileSize * columns);

			character++;
			if (rows == 0 && columns == 0)
			{
				KeyBoardComponent->m_IsActive = true;
			}
			scene.Add(LetterGameObject);
			objects.push_back(LetterGameObject);

		}

	}


	scene.AddObjects(objects);

	int currentTileActive = 0;

	//scene.objects 

	std::unique_ptr<dae::Command> SetSceneCommand{ std::make_unique<dae::ChangeSelectionCommand>(objects,currentTileActive,Direction::LEFT) };// one of when isntantiating a class 
	keyboard2->MapCommandToButton(SDL_SCANCODE_LEFT, std::move(SetSceneCommand), dae::ButtonState::Up);

	//will have to make it o
	SetSceneCommand = std::make_unique<dae::ChangeSelectionCommand>(objects, currentTileActive,Direction::RIGHT);// one of when isntantiating a class 
	keyboard2->MapCommandToButton(SDL_SCANCODE_RIGHT, std::move(SetSceneCommand), dae::ButtonState::Up);

	SetSceneCommand = std::make_unique<dae::ChangeSelectionCommand>(objects, currentTileActive,Direction::UP);// one of when isntantiating a class 
	keyboard2->MapCommandToButton(SDL_SCANCODE_UP, std::move(SetSceneCommand), dae::ButtonState::Up);

	SetSceneCommand = std::make_unique<dae::ChangeSelectionCommand>(objects, currentTileActive,Direction::DOWN);// one of when isntantiating a class 
	keyboard2->MapCommandToButton(SDL_SCANCODE_DOWN, std::move(SetSceneCommand), dae::ButtonState::Up);





	std::unique_ptr<dae::Command> SkipLevelsCommand{ std::make_unique<dae::LockInCommand>(objects) };// one of when isntantiating a class 
	keyboard2->MapCommandToButton(SDL_SCANCODE_RETURN, std::move(SkipLevelsCommand), dae::ButtonState::Up);


	//with enter 

	CreateButton(scene, " When you are ready press 5 on Keybaord Or Y On the controller ", 10, 440, SDL_Color{ 255,255,255,255 }, 25,"Empty");



	auto NameObject = std::make_shared<dae::GameObject>();
	auto pFrameRateRenderer = std::make_shared<dae::RenderComponent>();
	auto pTextComponent = std::make_shared<dae::TextComponent>(pFrameRateRenderer, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 30));
	auto playerNameComponent = std::make_shared<dae::DisplayNameComponent>(pTextComponent);
	playerNameComponent->m_IsName = true;
	pTextComponent->SetColor({ 255,200,0 });
	NameObject->AddComponent(pTextComponent);
	NameObject->AddComponent(playerNameComponent);
	NameObject->AddComponent(pFrameRateRenderer);
	NameObject->SetPosition(100, 400);
	scene.Add(NameObject);






}

void LoadCoOpScene()
{

	auto& scene = dae::SceneManager::GetInstance().CreateScene(CO_OP_SCENE);

	std::vector <std::shared_ptr<dae::GameObject>> m_GameObjects;
	CreateBackGround(scene);

	//////////////////////////////////////////////////////////
	auto PengoGameObject = CreatePengoPlayer(scene,100.f,100.f);
	auto PengoGameObject2 = CreatePengoPlayer(scene,200.f,100.f,false);

	auto MapGameObject = CreateMap(scene, PengoGameObject, "../Data/Map1.txt", 4,PengoGameObject2);
	auto MapComponent = MapGameObject->GetComponent<dae::MapComponent>();

	auto Tiles = MapComponent->GetTiles();
	Tiles.push_back(PengoGameObject);  //scene.add Player 2 
	Tiles.push_back(PengoGameObject2);  ///addd Player 2 here  here 


	DisplayScore(scene, MapGameObject);
	DisplayLives(scene, PengoGameObject);

	//pathfinding on only one Player 
	CreateEnemyManager(MapGameObject, Tiles, PengoGameObject, scene, "MIGUEL_Enemy_RED.png");





	

}

void LoadScoresScene()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene(SCORE_SCENE);  //creaate scene   
	//CreateButton(scene, "Highest Score",70,30);


	CreateButton(scene, " Max Scores ", 30, 20, SDL_Color{ 255,255,255,255 }, 120,"");


	CreateButton(scene, " Press B on controller to restart Game ", 30, 650, SDL_Color{ 255,255,255,255 },30,"");




	//name of player 


	float X{ 40 };
	auto NameObject = std::make_shared<dae::GameObject>();
	auto pFrameRateRenderer = std::make_shared<dae::RenderComponent>();
	auto pTextComponent = std::make_shared<dae::TextComponent>(pFrameRateRenderer, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 50));
	auto playerNameComponent = std::make_shared<dae::DisplayNameComponent>(pTextComponent);
	playerNameComponent->m_IsName = true;
	pTextComponent->SetColor({ 255,250,0 });
	NameObject->AddComponent(pTextComponent);
	NameObject->AddComponent(playerNameComponent);
	NameObject->AddComponent(pFrameRateRenderer);
	NameObject->SetPosition(X, 300);
	scene.Add(NameObject);




	////score
	auto PlayerScore = std::make_shared<dae::GameObject>();
	auto PlayerScoreRenderer = std::make_shared<dae::RenderComponent>();
	auto pTextComponent2 = std::make_shared<dae::TextComponent>(PlayerScoreRenderer, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 100));
	auto playerScoreComponent = std::make_shared<dae::DisplayNameComponent>(pTextComponent2);
	playerScoreComponent->m_IsScore = true;  //change 
	pTextComponent2->SetColor({ 255,200,0 });
	PlayerScore->AddComponent(pTextComponent2);
	PlayerScore->AddComponent(playerScoreComponent);
	PlayerScore->AddComponent(PlayerScoreRenderer);
	PlayerScore->SetPosition(X -30, 360);
	scene.Add(PlayerScore);


	//highes

	auto HighesScore = std::make_shared<dae::GameObject>();
	auto HighesScoreRenderer = std::make_shared<dae::RenderComponent>();
	auto pTextComponent3 = std::make_shared<dae::TextComponent>(HighesScoreRenderer, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 35));
	auto playerScoreComponen3 = std::make_shared<dae::DisplayNameComponent>(pTextComponent3);
	playerScoreComponen3->m_IsHighestScore = true;  //change 
	pTextComponent2->SetColor({ 255,200,0 });
	HighesScore->AddComponent(pTextComponent3);
	HighesScore->AddComponent(playerScoreComponen3);
	HighesScore->AddComponent(HighesScoreRenderer);
	HighesScore->SetPosition(20, 190);
	scene.Add(HighesScore);


}

void LoadVersusMode()
{

	auto& scene = dae::SceneManager::GetInstance().CreateScene(VERSUS_MODE);
	
	std::vector <std::shared_ptr<dae::GameObject>> m_GameObjects;
	CreateBackGround(scene);

	//////////////////////////////////////////////////////////
	auto PengoGameObject = CreatePengoPlayer(scene,100.f,100.f);

	auto MapGameObject = CreateMap(scene, PengoGameObject, "../Data/Map1.txt", 2,nullptr);
	auto MapComponent = MapGameObject->GetComponent<dae::MapComponent>();

	auto Tiles = MapComponent->GetTiles();
	Tiles.push_back(PengoGameObject);


	auto enemymanager = CreateEnemyManager(MapGameObject, Tiles, PengoGameObject, scene, "MIGUEL_Enemy_RED.png");

	//enemy player 

	auto Enemy = std::make_shared<dae::GameObject>();
	auto EnemyRenderer = std::make_shared<dae::RenderComponent>(-2, true);
	auto EnemyPengoComponent = std::make_shared<dae::PengoComponent>();
	auto EnemyRectComponent = std::make_shared<dae::RectangleComponent>(30, 30);
	auto CollisionComponentEnmies = std::make_shared<dae::CollisionWithComponent>(Tiles);
	auto CollisionResponseEnemy = std::make_shared<dae::CollsionResponse>();
	auto EnemySpawner = enemymanager->GetComponent<dae::EnemySpawner>();
	CollisionResponseEnemy->m_EnemySpawner = EnemySpawner.get();
	EnemySpawner->m_NumberActiveEnemies++;
	EnemyRenderer->SetTexture("MIGUEL_Enemy_RED.png");
	EnemyRenderer->AddToVector(5, 8, 5, 5, dae::AnimationComponent::Type::loop, 0, 1);//down
	EnemyRenderer->AddToVector(5, 8, 5, 5, dae::AnimationComponent::Type::loop, 0, 1);//down
	EnemyRenderer->AddToVector(5, 8, 5, 5, dae::AnimationComponent::Type::loop, 0, 1);//down
	EnemyRenderer->AddToVector(5, 8, 5, 5, dae::AnimationComponent::Type::loop, 0, 1);//down
	EnemyRenderer->SetDimension(2.5f);
	Enemy->AddComponent(EnemyRenderer);
	Enemy->AddComponent(EnemyRectComponent);
	Enemy->AddComponent(CollisionComponentEnmies);
	Enemy->AddComponent(CollisionResponseEnemy);
	Enemy->AddComponent(EnemyPengoComponent);
	Enemy->SetPosition(624,624);
	scene.AddEnemy(Enemy);
	scene.Add(Enemy);

	auto mapcom = MapGameObject->GetComponent<dae::MapComponent>();
	if (mapcom)
	{
		mapcom->SetPlayer2(Enemy);
	}

	DisplayScore(scene, MapGameObject);
	DisplayLives(scene, PengoGameObject);
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
	audio.Play(S_EnemyDead, 0.5f, 100);



	audio.AddSound("EnemyDeath.mp3", S_EnemyDead, false);   //is music  was true

	audio.AddSound("EnemySpawned.mp3",s_EnemySpawned, false);   //is music  was true

	audio.AddSound("ScoresSceneSound.mp3",S_ScoresSceneSound, false);   //is music  was true
	//played when hetting key

	audio.Preload(S_CubesAligned);
	
	audio.AddSound("BonusDiamond.mp3", S_CubesAligned,false); 


	audio.Preload(s_KeyBoardkeyMusic);
	audio.AddSound("keyboard-spacebar-hit-101812.mp3", s_KeyBoardkeyMusic,false);

	audio.Preload(S_PengoDeath);
	audio.AddSound("PengoDeath.mp3", S_PengoDeath,true);


	//ice block destroyed
	audio.Preload(s_IceBlockDestroyed);  //preload
	audio.AddSound("IceBlockDestroyed.mp3", s_IceBlockDestroyed,false);

	/// pushed blockd
	audio.Preload(s_PushedBlockSound);
	audio.AddSound("PushedBlock.mp3", s_PushedBlockSound,false);


	/*IceBlockDestroyed.mp3
		PushedBlock.mp3*/



	LoadMenuScene();

	Level1();
	Level2();
	Level3();


	LoadCoOpScene();
	LoadVersusMode();
	InputNameScene();
	LoadScoresScene();

	dae::SceneManager::GetInstance().SetCurrentScene(MENU_SCENE);
}


int main(int, char * [])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);  //load all scenes at once 
	return 0;
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
std::shared_ptr<dae::GameObject> CreatePengoPlayer(dae::Scene & scene,float X,float Y,bool IsPlayerOne)
{
	auto PengoGameObject = std::make_shared<dae::GameObject>();
	auto PengoRenderer = std::make_shared<dae::RenderComponent>(-2, true);
	auto PengoComponent = std::make_shared<dae::PengoComponent>();
	auto LivesComponent = std::make_shared<dae::LivesComponent>();
	auto PengoRectComponent = std::make_shared<dae::RectangleComponent>(16, 16);
	auto CollisionResponse = std::make_shared<dae::CollsionResponse>();
	auto TagComponent = std::make_shared<dae::TagComponent>(PENGO);
	PengoRectComponent->m_Active = true;
	PengoRenderer->SetTexture("Pengo.png");
	PengoRenderer->SetDimension(2.4f);       //was 0.5     
	PengoRenderer->AddToVector(3, 8, 2, 5, dae::AnimationComponent::Type::loop, 0, 0);//down
	PengoRenderer->AddToVector(3, 8, 4, 5, dae::AnimationComponent::Type::StartAtNoZero, 2, 0);//left
	PengoRenderer->AddToVector(3, 8, 6, 5, dae::AnimationComponent::Type::StartAtNoZero, 4, 0); //up
	PengoRenderer->AddToVector(3, 8, 8, 5, dae::AnimationComponent::Type::StartAtNoZero, 6, 0); //right
	PengoGameObject->AddComponent(PengoComponent);
	PengoGameObject->AddComponent(PengoRectComponent);
	PengoGameObject->AddComponent(PengoRenderer);
	PengoGameObject->AddComponent(CollisionResponse);
	PengoGameObject->AddComponent(TagComponent);
	PengoGameObject->AddComponent(LivesComponent);

	PengoGameObject->SetPosition(X,Y);
	scene.Add(PengoGameObject);


	if (IsPlayerOne)
	{
	scene.AddPlayer(PengoGameObject);

	}
	else
	{
		scene.AddPlayer2(PengoGameObject);

	}

	return PengoGameObject;
	
}
std::shared_ptr<dae::GameObject> CreateMap(dae::Scene& scene,std::shared_ptr<dae::GameObject> PengoGameObject, const std::string & MapFileName,int numberEnmies,std::shared_ptr<dae::GameObject> player2)
{
	auto MapGameObject = std::make_shared<dae::GameObject>();
	auto MapComponent = std::make_shared<dae::MapComponent>(PengoGameObject, MapFileName, numberEnmies,player2);
	MapGameObject->AddComponent(MapComponent);
	scene.Add(MapGameObject);
	scene.AddMap(MapGameObject);

	return MapGameObject;


}
void CreateBackGround(dae::Scene& scene)
{
	auto BackGroundGameObject = std::make_shared<dae::GameObject>();
	auto BackGroundImageRender = std::make_shared<dae::RenderComponent>(-1, false);
	BackGroundImageRender->SetTexture("MIGUEL_Border_3.png");
	BackGroundImageRender->SetDimension(1.f);
	BackGroundGameObject->AddComponent(BackGroundImageRender);
	BackGroundGameObject->SetPosition(0, 0);
	scene.Add(BackGroundGameObject);

}
std::shared_ptr<dae::GameObject> CreateEnemyManager(std::shared_ptr<dae::GameObject>& MapGameObject, std::vector<std::shared_ptr<dae::GameObject>>& Tiles, std::shared_ptr<dae::GameObject>& PengoGameObject, dae::Scene& scene, const std::string filename)
{
	auto GameManagerGameOject = std::make_shared<dae::GameObject>();
	auto GameManagerComponent = std::make_shared<dae::GameManagerComponent>(MapGameObject);
	auto EnemySpawnerComponent = std::make_shared<dae::EnemySpawner>(Tiles, MapGameObject, PengoGameObject, filename);
	GameManagerGameOject->AddComponent(GameManagerComponent);
	GameManagerGameOject->AddComponent(EnemySpawnerComponent);
	scene.Add(GameManagerGameOject);

	return GameManagerGameOject;

}



