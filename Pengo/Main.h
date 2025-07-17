#pragma once

void CreateMap(dae::Scene& scene, std::vector<std::shared_ptr<dae::GameObject>>& CubesVector);

void DrawInvisibleDotsmainLevel(std::shared_ptr<dae::GameObject>& Qbert, dae::Scene& scene);
void DrawInvisibleDotsmainSnake(std::shared_ptr<dae::GameObject>& Qbert, dae::Scene& scene);

void DrawButtonRectMainLevel(std::shared_ptr<dae::GameObject>& Qbert, dae::Scene& scene);

void ChangeToCube(dae::Scene& scene,int index);

void PlayerText(dae::Scene& scene);

void DrawDetails(dae::Scene& scene);

void DisplayScore(dae::Scene& scene);

void CreatePlatforms(std::shared_ptr<dae::GameObject>& Qbert, dae::Scene& scene);

void DrawButtonRectSnake(std::shared_ptr<dae::GameObject>& Snake, dae::Scene& scene);

void CreateBottomRectEnemies(std::shared_ptr<dae::GameObject>& PinkDot, dae::Scene& scene);

void DrawBottomRectTutorial(std::shared_ptr<dae::GameObject>& Qbert, dae::Scene& scene);

void DrawInvisibleDotsTutorial(std::shared_ptr<dae::GameObject>& Qbert, dae::Scene& scene);

void DrawNumber(dae::Scene& scene, int level);

void DisplayLives(dae::Scene& scene);

void CreateBackGround(dae::Scene& scene);
