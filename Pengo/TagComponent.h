#pragma once
#include"Component.h"
#include<memory>
#include"SDL.h"
#include<string>
namespace dae
{
    class GameObject;

    class TagComponent final : public Component
    {
    public:

        TagComponent(const std::string & tag);
        virtual ~TagComponent() = default;
        TagComponent(const TagComponent& other) = default;
        TagComponent(TagComponent&& other) = default;
        TagComponent& operator=(const TagComponent& other) = default;
        TagComponent& operator=(TagComponent&& other) = default;
        void  Update() override;
        void  Render() override;
        std::string GetTag();
    private:

        std::string m_tag{};



    };
}