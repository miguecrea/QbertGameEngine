#include "staticHeader.h"
#include<string>

int m_pacmanState = 1;
int m_MrsPacmanState = 1;
int m_GhostState = 0;

 int S_EnemyDead = 0;   
 int s_MenuMusicId=0; 
 int s_EndMusicId=0;

 int s_IceBlockDestroyed = 0;
 int S_CubesAligned= 1;
 int s_KeyBoardkeyMusic= 2;
 int s_PushedBlockSound = 3;
 int S_PengoDeath = 4;
 int S_ScoresSceneSound = 5;
 int s_EnemySpawned = 6;

 int s_Score = 0;
 int s_HighScore = 0;
 int s_Lives = 3;
 int s_ScoreIncrease = 50;
 std::string s_PlayerName;
 std::string s_HighesScorePlayerName ="empty";
 int s_PauseGame =  0;
 int s_CurrentCharacter = 0;
 bool s_CanUseInput = true;
 bool s_ResetGame = false;
