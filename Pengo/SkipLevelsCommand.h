#pragma once

#include"Command.h"

namespace dae
{

    class InputManager;
    class Scene;
    class SkipLevelsCommand final : public Command
    {
    public:
        SkipLevelsCommand();
        void Execute() override;
        void ClearInputBindings(dae::InputManager& input,Scene * scene);
        void ChooseScene();
        virtual void Undo() override;

      void AddToIndex();

        static int m_index;
    private:
 
        const int MAX_NUMBER_SCENES = 3;
    };
}

