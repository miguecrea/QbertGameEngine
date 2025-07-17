#pragma once

#include"InputManager.h"
#include"GameObject.h"
#include <memory>
#include"RenderComponent.h"



void AddControllerKeyboardPlayer1(std::shared_ptr<dae::GameObject>& Qbert, std::shared_ptr<dae::RenderComponent>& QbertRenderer);
void AddControllerKeyboardPlayer2(std::shared_ptr<dae::GameObject>& snake, std::shared_ptr<dae::RenderComponent>& snakeRenderer);
