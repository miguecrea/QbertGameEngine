#include "DisplayNameComponent.h"
#include"staticHeader.h"
#include"iostream"
#include <fstream>
dae::DisplayNameComponent::DisplayNameComponent(std::shared_ptr<TextComponent> pTextComponent):
	m_pTextComponent{pTextComponent}
{
}
void dae::DisplayNameComponent::Update()
{
	if (m_IsHighestScore)
	{
		auto highScoreData = readMaxScore("max.txt");
		s_HighScore = highScoreData.first;
		s_HighesScorePlayerName = highScoreData.second;

		if (s_Score > s_HighScore) 
		{
			writeMaxScore("max.txt", s_Score, s_PlayerName);
			s_HighScore = s_Score;
			s_HighesScorePlayerName = s_PlayerName;
		}
		else {
			std::cout << "No new high score." << std::endl;
		}

	}

	if (m_pTextComponent)
	{

		if (m_IsName)
		{
			m_pTextComponent->SetTextToTexture("Player Name is : " + s_PlayerName);
		}

		else if (m_IsScore)
		{
			m_pTextComponent->SetTextToTexture(" Score " + std::to_string(s_Score));
		}

		else if (m_IsHighestScore)
		{
			m_pTextComponent->SetTextToTexture("HighestScore is: " + std::to_string(s_HighScore) + "name is" + s_HighesScorePlayerName);

		}else if (m_IsLives)
		{
			m_pTextComponent->SetTextToTexture("Lives Remaining: " + std::to_string(s_Lives));

		}

	}
}

void dae::DisplayNameComponent::writeMaxScore(const std::string& filename, int score, const std::string& playerName)
{
	std::ofstream file(filename);

	if (file.is_open()) {
		file << score << std::endl;
		file << playerName << std::endl;
		file.close();
	}
	else {
		std::cerr << "Unable to open file for writing." << std::endl;
	}
}


std::pair<int, std::string> dae::DisplayNameComponent::readMaxScore(const std::string& filename)
{
	std::ifstream file(filename);
	int maxScore = 0;
	std::string playerName;

	if (file.is_open()) {
		file >> maxScore;
		file.ignore();  // Ignore the newline character after the score
		std::getline(file, playerName);
		file.close();
	}

	return std::make_pair(maxScore, playerName);
}
